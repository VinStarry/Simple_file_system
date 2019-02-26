//
// Created by 永鑫   徐 on 2019-02-26.
//

#ifndef VFS_DATA_STRUCTURES_H
#define VFS_DATA_STRUCTURES_H

typedef unsigned uid_t;
typedef unsigned long blkcnt_t;
typedef unsigned short u_mode_t;


struct super_block {
    unsigned long s_blocknumbers;   // 块的总数量
    unsigned long s_blocksize;      // 块的大小
    struct inode_linked_list *s_inodes; // 超级快的i节点链表
    void *s_bdev;       // 存储块
    int s_bitmap_blks;  // 位示图的块数量
};

struct inode {
    struct super_block *i_sb;
    unsigned long i_no;
    uid_t i_uid;
    blkcnt_t i_blocks;
    unsigned long i_btyes;
    u_mode_t mode;
};

struct dentry {
    struct inode *d_indoe;
    struct hash_table *subdirs;
    unsigned long d_time;
    struct super_block *d_sb;
    char d_iname;
    struct dentry *parent;
};

#endif //VFS_DATA_STRUCTURES_H
