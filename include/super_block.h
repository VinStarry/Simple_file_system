//
// Created by 永鑫   徐 on 2019-02-25.
//

#ifndef VFS_SUPER_BLOCK_H
#define VFS_SUPER_BLOCK_H

#include <stdio.h>
#include <memory.h>
#include <stdbool.h>
#include "../include/data_structures.h"
#include "../include/inode.h"
#include "../include/dentry.h"

#define BLK_SIZE 1024
#define BLK_NUM 102400

struct super_block *init_block(struct dentry *root);
struct super_block *free_block(struct super_block *sb);
bool save_block(struct super_block *sb);
struct super_block *load_block(struct dentry *root);
struct inode *alloc_inode(struct super_block *sb);
void destroy_inode(struct inode *inode);
size_t write_block(struct super_block *sb, unsigned long block_no, char *stream, size_t size);
size_t read_block(struct super_block *sb, unsigned long block_no, char *stream, size_t size);
bool occupy_block(blkcnt_t blk_no, struct super_block *sb);
bool release_block(blkcnt_t blk_no, struct super_block *sb);
bool alloc_block_for_inode(struct super_block *sb, struct inode *inode);
void *free_block_for_inode(struct super_block *sb, struct inode *inode);
void *alloc_data_block(struct super_block *sb);

#endif //VFS_SUPER_BLOCK_H
