#include<iostream>
#include<thread>
//CAS
struct Node{
    public:
        Node(int v):value(v){}
        int value = 0;
        struct Node* next = nullptr;
};

Node* head = nullptr;
Node* tail = nullptr;

//初始化时默认填入一个节点,便于处理边界条件head tail指向同一个节点的问题
void init()
{
    Node* n = new Node(-1);
    n->next = nullptr;
    head = n;
    tail = n;
}
//假如线程A添加完元素后，切换线程B运行，B线程的while循环退不出来，因为A线程更新了tail->next.
//总有一个时间点系统调度线程A继续运行，继续执行第二CAS来更新tail，且一定不会失败，因为其它线程都
//卡在while循环里出不来，更本没有机会去更新tail，自然线程A的第二个CAS不可能失败。
//但是该写法依然存在问题。当某个线程在退出while循环后，执行tail指向新尾节点时，如果此时该线程退出，
//就会造成其它线程永远在while循环中退不出来
void enqueue1(Node* node)
{
    Node* p = nullptr;
    do
    {
        p = tail;
    }
    while(!__sync_bool_compare_and_swap(&p->next, nullptr, node));
    __sync_bool_compare_and_swap(&tail, p, node);
}

//为了解决enqueue1的问题，在while循环体中遍历节点，自己找到尾节点，在后面添加新节点并退出while循环，
//此后再继续更新tail指向新的尾节点。即使在更新tail时程序挂了，其它线程也可以自己遍历到队列末尾添加元素。
//每个线程第二个CAS无论成功失败都不重要，如果某个线程更新tail失败，其它线程可以继续添加元素同时更新tail，
//即使其它线程也更新失败也不影响队列继续插入元素，总会有一个线程是最后向队列插入元素的线程,那么这个线程的第二个
//CAS操作就会成功,最终只要有一个线程更新tail成功即可。
//但是此种写法效率不高，因为每个线程都要遍历节点移动到尾节点，在线程非常多或者插入非常频繁的场景下，对效率的影响很大
void enqueue2(Node* node)
{
    Node* p = tail;
    Node* old_tail = p;
    do
    {
        while(p->next != nullptr)
            p = p->next;
    }
    while(!__sync_bool_compare_and_swap(&p->next, nullptr, node));
    __sync_bool_compare_and_swap(&tail, old_tail, node);
}

//为解决enqueue2的问题做如下改动,但这只解决了部分问题,ABA问题并未得到有效解决
void enqueue3(Node* node)
{
    Node* local_tail = nullptr;
    Node* next = nullptr;
    while(true)
    {
        //把tail和tail->next保存下来
        local_tail = tail;
        next = local_tail->next;
        //在保存过程中，tail被其它线程修改了则重试
        if(tail != local_tail)
            continue;

        //在保存过程中，tail未被其它线程修改，但是其它线程在tail后追加元素了则遍历到末尾
        if(next != nullptr)
        {
            __sync_bool_compare_and_swap(&tail, local_tail, next);
        }
        else if(__sync_bool_compare_and_swap(&local_tail->next, next, node))//在保存过程中，tail未被其它线程修改且未追加元素则把node追加到末尾
            break;
    }

    __sync_bool_compare_and_swap(&tail, local_tail, node);//更新tail
}

Node* dequeue()
{
    std::cout << "dequeue" << std::endl;

    Node* local_head = nullptr;
    do
    {
        local_head = head;//head是一个哑头节点,所以用下面用的是next
        if(nullptr == local_head->next)
        {
            std::cout << "is empty" << std::endl;
            return nullptr;
        }

    }while(!__sync_bool_compare_and_swap(&head, local_head, local_head->next));

    return local_head->next;
}


void* work()
{
    for(int i = 0; i < 100000; i++)
    {
        Node* n = new Node(i);
        enqueue2(n);
    }
}

int main()
{
    init();
    for(int i = 0; i< 5; i++)
    {
        auto th = std::thread(work);
        th.detach();
    }

    static int c = 0;
    while(true)
    {
        Node* n1 = dequeue();
        if(n1)
            std::cout << "n1=" << n1->value << std::endl;
        else
            break;
        c++;
    }
    std::cout<< "count=" << c << std::endl;
}




typedef uint64_t U8;

struct TNode {
    TNode* m_pNext;
};

template<class T>
union THead {
        struct {
                U8  m_nABA : 4;
                U8  m_pNode:60;  // Windows only supports 44 bits addressing anyway.
        };
        U8  m_n64; // for CAS
        // this constructor will make an atomic copy on intel
        THead(THead& r)         { m_n64 = r.m_n64; }
        T* Node()               { return (T*)m_pNode; }
        // changeing Node bumps aba
        void Node(T* p)         { m_nABA++; m_pNode = (U8)p; return this; }
};

// pop pNode from head of list.
template<class T>
T* Pop(volatile THead<T>& Head) {
    while (1) { // race loop
        // Get an atomic copy of head and call it old.
        THead<T> Old(Head);
        if (!Old.Node())
            return NULL;
        // Copy old and call it new.
        THead<T> New(Old);
        // change New's Node, which bumps internal aba
        New.Node(Old.Node()->m_pNext);
        // compare and swap New with Head if it still matches Old.
        if (CAS(&Head.m_n64, Old.m_n64, New.m_n64))
            return Old.Node(); // success
        // race, try again
    }
}

// push pNode onto head of list.
template<class T>
void Push(volatile THead<T>& Head, T* pNode) {
    while (1) { // race loop
        // Get an atomic copy of head and call it old.
        // Copy old and call it new.
        THead<T> Old(Head), New(Old);
        // Wire node t Head
        pNode->m_pNext = New.Node();
        // change New's head ptr, which bumps internal aba
        New.Node(pNode);
        // compare and swap New with Head if it still matches Old.
        if (CAS(&Head.m_n64, Old.m_n64, New.m_n64))
            break; // success
        // race, try again
    }
}
