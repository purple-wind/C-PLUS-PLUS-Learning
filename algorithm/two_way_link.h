#ifndef __TWO_WAY_LINK_H__
#define __TWO_WAY_LINK_H__
//创建存储区
void link_init(void);
//销毁存储区
void link_deinit(void);
//判断链表是否为空
int link_empty(void);
//在链表前端插入新节点
void link_insert_head(int);
//在链表末尾插入新节点
void link_append(int);
//删除链表第一个有效节点
void link_remove_head(void);
//删除链表最后一个有效节点
void link_remove_tail(void);
//计算链表中有效数字的个数
int link_size(void);
//获得第一个数据
int get_head(void);
//获得最后一个有效数据
int get_tail(void);
//按顺序插入新数字
void insert_in_order(int);
//删除指定数字函数
void link_remove(int);
//开始遍历
void link_begin(void);
//获得下一个数字
int link_next(void);

#endif /* __TWO_WAY_LINK_H__ */
