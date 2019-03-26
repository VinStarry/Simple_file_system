//
// Created by 永鑫   徐 on 2019-02-25.
//

#ifndef VFS_INODE_H
#define VFS_INODE_H

#include <stdlib.h>
#include "../include/data_structures.h"

struct inode_linked_list {
    struct inode *inode;
    struct inode_linked_list *next;
};

//struct inode_linked_list *init_inode_list(size_t num, struct super_block *sb);
//struct inode_linked_list *inode_list_free(struct inode_linked_list *ilist);
void get_inode_memory_by_num(struct inode *inode, struct super_block *sb);  // 根据i节点的序号得到i节点
void put_inode_memory_by_num(struct inode *inode, struct super_block *sb);  // 根据i节点的序号写入i节点的信息
bool test_block_free_by_inode_num(unsigned long inode_num, struct super_block *sb); // 查询i节点号所对应的块是否空闲
void fill_block_by_inode_num(unsigned long inode_num, struct super_block *sb);  // 写位示图

#endif //VFS_INODE_H
