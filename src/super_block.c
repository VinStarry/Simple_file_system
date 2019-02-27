//
// Created by 永鑫   徐 on 2019-02-25.
//

#include "../include/super_block.h"

const char * const save_path = "./data/blk_data.dat";

struct super_block *init_block(void) {
    struct super_block *sb = (struct super_block *)malloc(sizeof(struct super_block));
    sb->s_bdev = (char *)malloc(sizeof(char) * BLK_NUM * BLK_SIZE);
    sb->s_blocknumbers = BLK_NUM;
    sb->s_blocksize = BLK_SIZE;
    sb->s_bitmap_blks = (int)(BLK_NUM * 1.0 / BLK_SIZE / 8 + 0.5);
    sb->s_inodes = NULL;
    sb->s_inodes_num = 0;
    unsigned long offset = 0;
    memcpy(sb->s_bdev + offset, &sb->s_blocknumbers, sizeof(unsigned long));
    offset += sizeof(unsigned long);
    memcpy(sb->s_bdev + offset, &sb->s_blocksize, sizeof(unsigned long));
    offset += sizeof(unsigned long);
    memcpy(sb->s_bdev + offset, &sb->s_bitmap_blks, sizeof(int));
    offset += sizeof(int);
    memcpy(sb->s_bdev + offset, &sb->s_inodes_num, sizeof(unsigned long));
    offset += sizeof(unsigned long);

    int number_of_chars =  (sb->s_bitmap_blks + (sizeof(char) - 1)) / sizeof(char);
    char mask = 1;
    unsigned round = 0;
    const char char_mask = 0x01;
    int temp = sb->s_bitmap_blks;
    for (int i = 0; i < number_of_chars; i++) {
        for (int j = 0; j < sizeof(char) * 8; j++) {
            if (temp > 0) {
                temp--;
                mask = (mask << 1) | char_mask;
            }
            else {
                mask = (mask << 1) & (~char_mask);
            }
        }
        memcpy(sb->s_bdev + BLK_SIZE + round * sizeof(char), &mask, sizeof(char));
        round++;
    }
    memcpy(sb->s_bdev + BLK_SIZE + round * sizeof(char), 0, sizeof(char) * (sb->s_bitmap_blks - number_of_chars) * BLK_SIZE);
    return sb;
}

struct super_block *free_block(struct super_block *sb) {
    if (sb) {
        if (sb->s_bdev)
            free(sb->s_bdev);
        if (sb->s_inodes)
            inode_list_free(sb->s_inodes);
    }
    return NULL;
}

bool save_block(struct super_block *sb) {
    FILE *fp = fopen(save_path, "wb");
    if (!fp)
        return false;
    fwrite(sb->s_bdev, sb->s_blocknumbers * sb->s_blocksize, 1, fp);
    fclose(fp);
    return true;
}

struct super_block *load_block(void) {
    FILE *fp = fopen(save_path, "rb");
    if (!fp)
        return NULL;
    struct super_block *sb = (struct super_block *)malloc(sizeof(struct super_block));
    sb->s_bdev = (char *)malloc(sizeof(char) * BLK_NUM * BLK_SIZE);
    fread(sb->s_bdev, BLK_NUM * BLK_SIZE, 1, fp);
    fclose(fp);
    unsigned long offset = 0;
    memcpy(&sb->s_blocknumbers, sb->s_bdev + offset, sizeof(unsigned long));
    offset += sizeof(unsigned long);
    memcpy(&sb->s_blocksize, sb->s_bdev + offset, sizeof(unsigned long));
    offset += sizeof(unsigned long);
    memcpy(&sb->s_bitmap_blks, sb->s_bdev + offset, sizeof(int));
    offset += sizeof(int);
    memcpy(&sb->s_inodes_num, sb->s_bdev + offset, sizeof(unsigned long));
    offset += sizeof(unsigned long);

    if (sb->s_inodes_num == 0)
        sb->s_inodes = NULL;
    return sb;
}

struct inode *alloc_inode(struct super_block *sb) {
    struct inode *new_inode = (struct inode *)malloc(sizeof(struct inode));
    new_inode->i_blocks = 0;
    new_inode->i_sb = sb;
    new_inode->i_nlink = 0;
    new_inode->i_btyes = 0;
    new_inode->i_blocks = 0;
    new_inode->i_list = NULL;
    new_inode->i_no = sb->s_inodes_num;

    struct inode_linked_list *ptr = (struct inode_linked_list *)malloc(sizeof(struct inode_linked_list));
    ptr->inode = new_inode;
    ptr->next = NULL;

    if(sb->s_inodes == NULL) {
        sb->s_inodes = (struct inode_linked_list *)malloc(sizeof(struct inode_linked_list));
        sb->s_inodes->inode = NULL;
        sb->s_inodes->next = NULL;
    }
    ptr->next = sb->s_inodes->next;
    sb->s_inodes->next = ptr;
    sb->s_inodes_num++;

    return new_inode;
}
