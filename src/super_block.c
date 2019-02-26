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
    sb->s_inodes = init_inode_list(BLK_NUM, sb);
    sb->s_bitmap_blks = (int)(BLK_NUM * 1.0 / BLK_SIZE / 8 + 0.5);
    memcpy(sb->s_bdev, &sb->s_blocknumbers, sizeof(unsigned long));
    memcpy(sb->s_bdev + sizeof(unsigned long), &sb->s_blocksize, sizeof(unsigned long));
    memcpy(sb->s_bdev + 2 * sizeof(unsigned long), &sb->s_bitmap_blks, sizeof(int));

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
        if (sb->s_bdev) {
            free(sb->s_bdev);
        }
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
    memcpy(&sb->s_blocknumbers, sb->s_bdev, sizeof(unsigned long));
    memcpy(&sb->s_blocksize, sb->s_bdev + sizeof(unsigned long), sizeof(unsigned long));
    memcpy(&sb->s_bitmap_blks, sb->s_bdev + 2 * sizeof(unsigned long), sizeof(int));
    return sb;
}