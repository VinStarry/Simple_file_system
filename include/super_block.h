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

struct super_block *init_block(struct dentry *root);    //初始化超级块
struct super_block *free_block(struct super_block *sb); //释放超级块
bool save_block(struct super_block *sb);                //保存块到文件
struct super_block *load_block(struct dentry *root);    //从文件读取块
struct inode *alloc_inode(struct super_block *sb);      //分配i节点
bool occupy_block(blkcnt_t blk_no, struct super_block *sb); //位示图修改 占用
bool release_block(blkcnt_t blk_no, struct super_block *sb);//位示图修改 释放
void *free_block_for_inode(struct super_block *sb, struct inode *inode); //释放i节点
unsigned long alloc_data_block(struct super_block *sb); //为数据文件分配块
void free_data_block(unsigned long blk_no, struct super_block *sb); //释放为数据文件分配的块
size_t write_block(struct super_block *sb, unsigned long block_no, char *stream, size_t size);  // 对块进行写操作
size_t read_block(struct super_block *sb, unsigned long block_no, char *stream, size_t size);   // 对块进行读操作

#endif //VFS_SUPER_BLOCK_H
