#include "single_link.h"
#include <stdlib.h>
#include <stdio.h>
typedef struct Node {
    int num;
    struct Node* p_next;
} Node;

static struct Node head= {0,NULL},tail = {0,NULL};

void link_init ( void )
{
    head.p_next = & tail;
}

void link_deinit()
{
    if(link_empty())
        return;
    while ( head.p_next != &tail ) {
        struct Node* first = &head;
        struct Node* mid = first->p_next;
        struct Node* last = mid->p_next->p_next;
        head.p_next = last;
        free ( mid );
        mid = NULL;
    };
}

int link_empty()
{
    if ( head.p_next == &tail ) {
        return 1;
    } else {
        return 0;
    }
}

void  link_insert_tail( int num)
{
    struct Node* new_node = ( struct Node* ) malloc ( sizeof ( struct Node ) );
    new_node->num = num;
    new_node->p_next = NULL;
    if ( new_node ) {
        for ( struct Node* it = &head; it != &tail; it = it->p_next ) {
            if ( it->p_next == &tail ) {
                new_node->p_next = &tail;
                it->p_next = new_node;
                break;
            }
        }
    }
}

void link_insert_head(int num)
{
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->num = num;
    new_node->p_next = NULL;
    struct Node* head_next = head.p_next;
    new_node->p_next = head_next;
    head.p_next = new_node;
}

void link_remove_head()
{
    if(link_empty())
        return;
    
    struct Node* next_next = head.p_next->p_next;
    free(head.p_next);
    head.p_next = NULL;
    head.p_next = next_next;
}

void link_remove_tail()
{
    if(link_empty())
        return;
    
    for(struct Node* it = &head;it != &tail ; it = it->p_next)
    {
        struct Node* it_next = it->p_next;
        struct Node* it_next_next = it->p_next->p_next;
        if(it_next_next == &tail)
        {
            it->p_next = &tail;
            free(it_next);
            it_next = NULL;
            break;
        }
    }
}

void link_remove(int num)
{
    if(link_empty())
        return;
    
    for(struct Node* it = &head;it != &tail;it = it->p_next)
    {
        struct Node* next = it->p_next;
        struct Node* next_next = next->p_next;
        
        if(it->p_next->num == num)
        {
             it->p_next = next_next;
             free(next);
             next = NULL;
             return;
        }
        else if(next_next == &tail)
        {
            break;
        }
    }
}

int link_size()
{
    int count =0;
    for(struct Node* it = head.p_next; it != &tail; it = it->p_next)
    {
        count++;
    }
    return count;
}

int link_get_head()
{
    if(link_empty())
        return -1;
    return head.p_next->num;
}

int link_get_tail()
{
    if(link_empty())
        return -1;
    for(struct Node* it = head.p_next;it != &tail; it = it->p_next)
    {
        if (it->p_next == &tail)
            return it->num;
    }
}



void link_reverse()
{
    if ( link_empty() ) {
        return;
    }

    struct Node* cur_head = &tail;
    for ( struct Node* it = head.p_next; it != &tail; ) {
        struct Node* next = it->p_next;
        it->p_next = cur_head;
        cur_head = it;
        it = next;
    }
    head.p_next = cur_head;
}


void link_for_each()
{
    for(struct Node* it = head.p_next; it != &tail; it = it->p_next)
    {
        printf("node=%d\n",it->num);
    }
}



