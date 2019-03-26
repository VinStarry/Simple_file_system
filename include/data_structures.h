//
// Created by 永鑫   徐 on 2019-02-26.
//

#ifndef VFS_DATA_STRUCTURES_H
#define VFS_DATA_STRUCTURES_H

#define DNAME_LEN 100
#define HASH_TABLE_ROW 10

typedef unsigned long blkcnt_t;
typedef unsigned long u_mode_t;

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

typedef struct ___str__list {
    char *str;
    char type;
    struct ___str__list *next;
}slist;

struct dir_hash_table {
    int hash_key;       // 哈希值
    char *dname;        // 目录名
    struct dentry *corres_dentry;   // 相对应的目录
    struct dir_hash_table *next;    // 链表元素
};

struct super_block {
    unsigned long s_blocknumbers;   // 块的总数量
    unsigned long s_blocksize;      // 块的大小
    void *s_bdev;       // 存储块
    int s_bitmap_blks;  // 位示图的块数量
};

struct inode {
    struct super_block *i_sb;   // 节点对应的超级块
    struct blk_lists *i_list;   // i节点所对应的块链表
    unsigned long i_nlink;      // i节点被硬链接的数量
    unsigned long i_no;         // i节点的编号
    unsigned long i_uid;        // i节点所属的用户的id
    blkcnt_t i_blocks;          // i节点占用的块数量
    unsigned long i_btyes;      // i节点的大小，以Byte为单位
    u_mode_t mode;              // 模式
};

struct dentry {
    char type;                  // 目录项的类型
    struct inode *d_inode;      // 对应的i节点
    struct dir_hash_table *subdirs[HASH_TABLE_ROW]; // 子目录hash表
    struct tm *d_time;          // 创建的时间
    struct super_block *d_sb;   // 对应的超级块
    struct dentry *parent;      // 父目录
    char d_iname[DNAME_LEN];    // 目录项的名称
};

#endif //VFS_DATA_STRUCTURES_H
