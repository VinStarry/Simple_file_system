//
// Created by 永鑫   徐 on 2019-02-26.
//

#ifndef VFS_DATA_STRUCTURES_H
#define VFS_DATA_STRUCTURES_H

#define DNAME_LEN 100
#define HASH_TABLE_ROW 10

typedef unsigned uid_t;
typedef unsigned long blkcnt_t;
typedef unsigned short u_mode_t;

#include "trival_helper.h"
#include "user.h"

enum d_type {
    __directory = 'd',
    __link = 'l',
    __file = '-'
};

struct blk_lists {
    blkcnt_t blk_no;
    unsigned long blk_len;
    struct blk_lists *next_blk;
};

typedef struct ___dentry__list {
    struct dentry *dir;
    struct ___dentry__list *next;
}dlist;

struct dir_hash_table {
    int hash_key;
    char *dname;
    struct dentry *corres_dentry;
    struct dir_hash_table *next;
};

struct super_block {
    unsigned long s_blocknumbers;   // 块的总数量
    unsigned long s_blocksize;      // 块的大小
//    struct inode_linked_list *s_inodes; // 超级块的空闲inode链表
//    unsigned long s_inodes_num;     // 空闲inode数量
    void *s_bdev;       // 存储块
    int s_bitmap_blks;  // 位示图的块数量
};

struct inode {
    struct super_block *i_sb;
    struct blk_lists *i_list;
    unsigned long i_nlink;
    unsigned long i_no;
    uid_t i_uid;
    blkcnt_t i_blocks;
    unsigned long i_btyes;
    u_mode_t mode;
};

struct dentry {
    char type;
    struct inode *d_inode;
    struct dir_hash_table *subdirs[HASH_TABLE_ROW];
    struct tm *d_time;
    struct super_block *d_sb;
    struct dentry *parent;
    char d_iname[DNAME_LEN];
};

#endif //VFS_DATA_STRUCTURES_H
