#include <sys/queue.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>

void test_tailq()
{
    std::cout << "---------------tailq---------------" << std::endl;
    struct Node0{
            int id;
            TAILQ_ENTRY(Node0) link;
    };
    //Node0展开如下
    //struct Node0{
    //        int id;
    //        struct {
    //                struct Node0 *tqe_next;
    //                struct Node0 * *tqe_prev;
    //        } link;
    //};

    TAILQ_HEAD(Head, Node0)* head = (struct Head*)malloc(sizeof(struct Head));
    //此句展开后如下
    //    struct Head {
    //            struct Node0 *tqh_first;
    //            struct Node0 * *tqh_last;
    //    }* head = (struct Head*)malloc(sizeof(struct Head));

    TAILQ_INIT(head);
    //此句展开后如下
    //(head)->tqh_first = __null;
    //(head)->tqh_last = &(head)->tqh_first;

    std::cout << (TAILQ_EMPTY(head) ? "empty" : "no empty") << std::endl;
    for(int i = 0; i < 5; i++)
    {
        struct Node0 *node = (struct Node0*)malloc(sizeof(struct Node0));
        node->id = i;
        TAILQ_INSERT_TAIL(head, node, link);
        //TAILQ_INSERT_HEAD(head, node, link);
    }
    std::cout << (TAILQ_EMPTY(head) ? "empty" : "no empty") << std::endl;


    struct Node0 *node = NULL;
    struct Node0 *var = NULL;
    node = (struct Node0*)malloc(sizeof(struct Node0));
    node->id = -2;

    //TAILQ_INSERT_BEFORE(TAILQ_FIRST(head), node, link);
    var = ((head)->tqh_first);
    TAILQ_INSERT_BEFORE(var, node, link);


    node = (struct Node0*)malloc(sizeof(struct Node0));
    node->id = -1;
    var = TAILQ_FIRST(head);
    TAILQ_INSERT_AFTER(head, var, node, link);




    std::cout << "forward traversal" << std::endl;
    TAILQ_FOREACH(var, head, link)
    {
        std::cout << "var->id=" << var->id << std::endl;
    }

    std::cout << "reverse traversal" << std::endl;
    TAILQ_FOREACH_REVERSE(var, head, Head, link)
    {
         std::cout << "var->id=" << var->id << std::endl;
    }

    std::cout << "first=" << TAILQ_FIRST(head)->id << std::endl;
    std::cout << "last="  << TAILQ_LAST(head, Head)->id << std::endl;

    var = TAILQ_LAST(head, Head);
    TAILQ_REMOVE(head, var, link);

    var = TAILQ_FIRST(head);
    TAILQ_REMOVE(head, var, link);

    std::cout << "after remove" << std::endl;
    TAILQ_FOREACH(var, head, link)
    {
        std::cout << "var->id=" << var->id << std::endl;
    }

    while(!TAILQ_EMPTY(head))
    {
        var = TAILQ_FIRST(head);
        TAILQ_REMOVE(head, var, link);
        free(var);
    }

    //等价于上面6行的删除操作，速度更快，更通用的方法
    //    var = TAILQ_FIRST(head);
    //    while (var != NULL) {
    //            struct Node0 *tmp = TAILQ_NEXT(var, link);
    //            TAILQ_REMOVE(head, var, link);
    //            free(var);
    //            var = tmp;
    //    }


    std::cout << (TAILQ_EMPTY(head) ? "empty" : "no empty") << std::endl;
}


void test_stailq()
{
    std::cout << "---------------stailq---------------" << std::endl;
    struct Node0{
            int id;
            STAILQ_ENTRY(Node0) link;
    };
    STAILQ_HEAD(Head, Node0) *head = (struct Head*)malloc(sizeof(struct Head));
    STAILQ_INIT(head);

    std::cout << (STAILQ_EMPTY(head) ? "empty" : "no empty") << std::endl;
    struct Node0 *node = NULL;
    struct Node0 *var = NULL;
    for(int i = 0; i < 5; i++)
    {
        node = (struct Node0*)malloc(sizeof(struct Node0));
        node->id = i;
        STAILQ_INSERT_TAIL(head, node, link);
    }
    std::cout << (STAILQ_EMPTY(head) ? "empty" : "no empty") << std::endl;


    node = (struct Node0*)malloc(sizeof(struct Node0));
    node->id = -1;
    STAILQ_INSERT_AFTER(head, STAILQ_FIRST(head), node, link);

    node = (struct Node0*)malloc(sizeof(struct Node0));
    node->id = -2;
    STAILQ_INSERT_AFTER(head, STAILQ_FIRST(head), node, link);


    STAILQ_FOREACH(var, head, link)
    {
        std::cout << "var->id=" << var->id << std::endl;
    }

    std::cout << "first=" << STAILQ_FIRST(head)->id << std::endl;


    var = STAILQ_FIRST(head);
    STAILQ_REMOVE(head, var, Node0, link);
    STAILQ_REMOVE_HEAD(head, link);

    std::cout << "remove 2 first" << std::endl;
    STAILQ_FOREACH(var, head, link)
    {
        std::cout << "var->id=" << var->id << std::endl;
    }

    //因为stailq支持STAILQ_REMOVE_HEAD函数，所以可以用此方法释放
    //while(!STAILQ_EMPTY(head))
    //{
    //    var = STAILQ_FIRST(head);
    //    STAILQ_REMOVE_HEAD(head, link);
    //    free(var);
    //}

    //通用的清空队列的方法
    //while(!STAILQ_EMPTY(head))
    //{
    //    var = STAILQ_FIRST(head);
    //    STAILQ_REMOVE(head, var, Node0, link);
    //    free(var);
    //}

    //等价于上面6行的删除操作，速度更快，更通用的方法
    var = STAILQ_FIRST(head);
    while(var)
    {
        struct Node0* tmp = STAILQ_NEXT(var, link);
        STAILQ_REMOVE(head, var, Node0, link);
        free(var);
        var = tmp;
    }
    std::cout << (STAILQ_EMPTY(head) ? "empty" : "no empty") << std::endl;

}

//同一个node节点的集合，可以通过两个链可以组织成两个队列。但是通过单个链添加或者移除的节点，只在自己的链上生效，其它的链无感知。
//因此在释放内存时要注意处理node节点集合中每个节点正确释放内存
//例如此例中head1队列中添加的二个元素，就不会通过head队列的释放而正确释放
void test_mutilqueue_tailq()
{
    std::cout << "---------------test_mutilqueue_tailq---------------" << std::endl;

    std::cout << "---------------stailq---------------" << std::endl;
    struct Node0{
            int id;
            STAILQ_ENTRY(Node0) link;
            TAILQ_ENTRY(Node0) timeout;
    };
    STAILQ_HEAD(Head, Node0) *head = (struct Head*)malloc(sizeof(struct Head));
    STAILQ_INIT(head);

    struct Node0 *node = NULL;
    struct Node0 *var = NULL;

    std::cout << "stailq " << (STAILQ_EMPTY(head) ? "empty" : "no empty") << std::endl;
    for(int i = 0; i < 5; i++)
    {
        struct Node0 *node = (struct Node0*)malloc(sizeof(struct Node0));
        node->id = i;
        STAILQ_INSERT_TAIL(head, node, link);
    }
    std::cout << "stailq " << (STAILQ_EMPTY(head) ? "empty" : "no empty") << std::endl;


     node = (struct Node0*)malloc(sizeof(struct Node0));
    node->id = -1;
    STAILQ_INSERT_AFTER(head, STAILQ_FIRST(head), node, link);

    node = (struct Node0*)malloc(sizeof(struct Node0));
    node->id = -2;
    STAILQ_INSERT_AFTER(head, STAILQ_FIRST(head), node, link);


    STAILQ_FOREACH(var, head, link)
    {
        std::cout << "var->id=" << var->id << std::endl;
    }

    std::cout << "first=" << STAILQ_FIRST(head)->id << std::endl;


    var = STAILQ_FIRST(head);
    STAILQ_REMOVE(head, var, Node0, link);
    STAILQ_REMOVE_HEAD(head, link);

    std::cout << "2 remove first" << std::endl;
    STAILQ_FOREACH(var, head, link)
    {
        std::cout << "var->id=" << var->id << std::endl;
    }

    std::cout << "stailq " << (STAILQ_EMPTY(head) ? "empty" : "no empty") << std::endl;



    std::cout <<" ---------------tailq-------------------" << std::endl;
    TAILQ_HEAD(Head1, Node0) *head1 = (struct Head1*)malloc(sizeof(struct Head1));
    TAILQ_INIT(head1);

    std::cout << "tailq " << (TAILQ_EMPTY(head1) ? "empty" : "no empty") << std::endl;
    STAILQ_FOREACH(var, head, link)
    {
        std::cout << "tailq insert var->id=" << var->id << std::endl;
        TAILQ_INSERT_TAIL(head1, var, timeout);
    }
    std::cout << "tailq " << (TAILQ_EMPTY(head1) ? "empty" : "no empty") << std::endl;


    node = (struct Node0*)malloc(sizeof(struct Node0));
    node->id = 0;
    TAILQ_INSERT_AFTER(head1, TAILQ_FIRST(head1), node, timeout);

    node = (struct Node0*)malloc(sizeof(struct Node0));
    node->id = -2;
    var = TAILQ_FIRST(head1);
    TAILQ_INSERT_BEFORE(var, node, timeout);

    TAILQ_FOREACH(var, head1, timeout)
    {
        std::cout << "var->id=" << var->id << std::endl;
    }

    var = TAILQ_FIRST(head1);
    TAILQ_REMOVE(head1, var, timeout);
    var = TAILQ_LAST(head1, Head1);
    TAILQ_REMOVE(head1, var, timeout);
    std::cout << "remove first and last" << std::endl;

    TAILQ_FOREACH(var, head1, timeout)
    {
        std::cout << "var->id=" << var->id << std::endl;
    }

    var = TAILQ_FIRST(head1);
    while(var != NULL)
    {
        struct Node0 *n0 = TAILQ_NEXT(var, timeout);
        TAILQ_REMOVE(head1, var, timeout);
        var = n0;
    }

    std::cout << "after tailq remove" << std::endl;
    std::cout << "tailq " << (TAILQ_EMPTY(head1) ? "empty" : "no empty") << std::endl;
    TAILQ_FOREACH(var, head1, timeout)
    {
        std::cout << "var->id=" << var->id << std::endl;
    }

    std::cout << "stailq " << (STAILQ_EMPTY(head) ? "empty" : "no empty") << std::endl;
    STAILQ_FOREACH(var, head, link)
    {
        std::cout << "var->id=" << var->id << std::endl;
    }

    //最后真正的释放node节点的内存后，head也被释放了,由于释放是通过head，所以只能释放head代表的队列节点，通过head1添加的二个节点内存未被释放，造成内存泄漏
    var = STAILQ_FIRST(head);
    while(var != NULL)
    {
        struct Node0 *tmp = STAILQ_NEXT(var, link);
        STAILQ_REMOVE(head, var, Node0, link);
        free(var);
        var = tmp;
    }
    std::cout << "after stailq free, stailq " << (STAILQ_EMPTY(head) ? "empty" : "no empty") << std::endl;
}

int main()
{
  test_tailq();
  test_stailq();
  test_mutilqueue_tailq();



    return 0;
}
