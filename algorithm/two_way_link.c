//创建存储区
#include <stdlib.h>
#include "two_way_link.h"
typedef struct node {
		int num;
		struct node *p_next;
		struct node *p_pre;
} node;
static node head, tail;
static node *p_cur;
void link_init(void) {
    head.p_next = &tail;
		tail.p_pre = &head;
}
//销毁存储区
void link_deinit(void) {
		while (head.p_next != &tail) {
				node *p_first = &head;
				node *p_mid = p_first->p_next;
				node *p_last = p_mid->p_next;
				p_first->p_next = p_last;
				p_last->p_pre = p_first;
				free(p_mid);
				p_mid = NULL;
		}
}
//判断链表是否为空
int link_empty(void) {
		return head.p_next == &tail;
}
//在链表前端插入新节点
void link_insert_head(int num) {
		node *p_tmp = (node *)malloc(sizeof(node));
		if (p_tmp) {
				node *p_first = &head;
				node *p_second = p_first->p_next;
				p_tmp->num = num;
				p_tmp->p_next = NULL;
				p_tmp->p_pre = NULL;
				p_first->p_next = p_tmp;
				p_tmp->p_pre = p_first;
				p_tmp->p_next = p_second;
				p_second->p_pre = p_tmp;
				p_cur = NULL;
		}
}
//在链表末尾插入新节点
void link_append(int num) {
		node *p_tmp = (node*)malloc(sizeof(node));
		if (p_tmp) {
				node *p_first = tail.p_pre;
				node *p_mid = p_first->p_next;
				node *p_last = p_mid->p_next;
				p_tmp->num = num;
				p_tmp->p_next = NULL;
				p_tmp->p_pre = NULL;
        p_first->p_next = p_tmp;
				p_tmp->p_pre = p_first;
				p_tmp->p_next = p_mid;
				p_mid->p_pre = p_tmp;
				p_cur = NULL;
		}
}
/*void link_append(int num) {
		node *p_node = NULL;
		node *p_tmp = (node*)malloc(sizeof(node));
		if (p_tmp) {
				p_tmp->num = num;
				p_tmp->p_next = NULL;
				p_tmp->p_pre = NULL;
		    for (p_node = &head;p_node != &tail;p_node = p_node->p_next) {
				    node *p_first = p_node;
				    node *p_mid = p_first->p_next;
				    node *p_last = p_mid->p_next;
				    if (p_mid == &tail) {
                p_first->p_next = p_tmp;
								p_tmp->p_pre = p_first;
								p_tmp->p_next = p_mid;
								p_mid->p_pre = p_tmp;
								p_cur = NULL;
								break;
				    }
		    }
		}
}*/
//删除链表第一个有效节点
void link_remove_head(void) {
		node *p_first = &head;
		node *p_mid = p_first->p_next;
		node *p_last = p_mid->p_next;
		p_first->p_next = p_last;
		p_last->p_pre = p_first;
		free(p_mid);
		p_mid = NULL;
		p_cur = NULL;
}
//删除链表最后一个有效节点
void link_remove_tail(void) {
		node *p_last = &tail;
		node *p_mid = p_last->p_pre;
		node *p_first = p_mid->p_pre;
		p_first->p_next = p_last;
		p_last->p_pre = p_first;
		free(p_mid);
		p_mid = NULL;
		p_cur = NULL;
}
/*void link_remove_tail(void) {
		node *p_node = NULL;
		for (p_node = &head;p_node != &tail;p_node = p_node->p_next) {
				node *p_first = p_node;
				node *p_mid = p_first->p_next;
				node *p_last = p_mid->p_next;
				if (p_last == &tail) {
						p_first->p_next = p_last;
						p_last->p_pre = p_first;
						free(p_mid);
						p_mid = NULL;
						p_cr = NULL;
				}
		}
}*/
//计算链表中有效数字的个数
int link_size(void) {
		int cnt = 0;
		node *p_node = NULL;
		for (p_node = &head;p_node != &tail;p_node = p_node->p_next) {
				node *p_first = p_node;
				node *p_mid = p_first->p_next;
				node *p_last = p_mid->p_next;
				if (p_mid != &tail) {
						cnt++;
				}
		}
		return cnt;
}

int get_head(void) {
		return head.p_next->num;
}

int get_tail(void) {
		return tail.p_pre->num;
}

void insert_in_order(int num) {
		node *p_node = NULL;
		for (p_node = &head;p_node != &tail;p_node = p_node->p_next) {
				node *p_first = p_node;
				node *p_mid = p_first->p_next;
				node *p_last = p_mid->p_next;
				if (p_mid == &tail || p_mid->num > num) {
						node *p_tmp = (node *)malloc(sizeof(node));
						if (p_tmp) {
						    p_tmp->num = num;
						    p_tmp->p_next = NULL;
						    p_tmp->p_pre = NULL;
								p_first->p_next = p_tmp;
								p_tmp->p_pre = p_first;
								p_tmp->p_next = p_mid;
								p_mid->p_pre = p_tmp;
								p_cur = NULL;
						}
						break;
				}
		}
}

void link_remove(int num) {
		node *p_node = NULL;
		for (p_node = &head;p_node != &tail;p_node = p_node->p_next) {
				node *p_first = p_node;
				node *p_mid = p_first->p_next;
				node *p_last = p_mid->p_next;
				if (p_mid != &tail && p_mid->num == num) {
						p_first->p_next = p_last;
						p_last->p_pre = p_first;
						free(p_mid);
						p_mid = NULL;
						p_cur = NULL;
						break;
				}
		}
}

void link_begin(void) {
		p_cur = head.p_next;
}

int link_next(void) {
		int tmp = 0;
		if (!p_cur) {
				return -1;
		}
		tmp = p_cur->num;
		p_cur = p_cur->p_next;
		if (p_cur == &tail) {
				p_cur = NULL;
		}
		return tmp;
}



