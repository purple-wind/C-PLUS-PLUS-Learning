/*单向链表*/
#ifndef __SINGLE_LINK_H__
#define __SINGLE_LINK_H__

#ifdef __cplusplus
extern "C"{
#endif
//创建存储区
void link_init(void);
// 销毁存储区
void link_deinit(void);
// 判断链表是否为空
int link_empty(void);
// 在链表前端插入节点
void link_insert_head(int);
// 在链表尾端插入节点
void link_insert_tail(int);
// 删除链表第一个有效节点
void link_remove_head(void);
// 删除链表最后一个有效节点
void link_remove_tail(void);
// 删除指定数字函数
void link_remove(int);
// 计算链表中有效数字的个数
int link_size(void);
// 获取第一个数据
int link_get_head(void);
// 获取最后一个数据
int link_get_tail(void);

void link_reverse(void);

// 开始遍历
void link_for_each();
#ifdef __cplusplus
}
#endif

#endif //__SINGLE_LINK_H__
