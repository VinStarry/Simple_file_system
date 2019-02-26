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

struct inode_linked_list *init_inode_list(size_t num, struct super_block *sb);
struct inode_linked_list *inode_list_free(struct inode_linked_list *ilist);

#endif //VFS_INODE_H
