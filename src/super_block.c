//
// Created by 永鑫   徐 on 2019-02-25.
//

#include "../include/super_block.h"

const char * const save_path = "./data/blk_data.dat";

struct super_block *init_block(struct dentry *root) {
    struct super_block *sb = (struct super_block *)malloc(sizeof(struct super_block));
    sb->s_bdev = (char *)malloc(sizeof(char) * BLK_NUM * BLK_SIZE);
    sb->s_blocknumbers = BLK_NUM;
    sb->s_blocksize = BLK_SIZE;
    sb->s_bitmap_blks = (int)(BLK_NUM * 1.0 / BLK_SIZE / 8 + 0.5);
//    sb->s_inodes = NULL;
//    sb->s_inodes_num = 0;

    root->parent = NULL;
    root->type = __directory;
    root->d_time = get_local_time();
    root->d_sb = sb;
    strcpy(root->d_iname, "/");
    root->d_inode = alloc_inode(sb);
    for (int i = 0; i < HASH_TABLE_ROW; i++) {
        root->subdirs[i] = (struct dir_hash_table *)malloc(sizeof(struct dir_hash_table));
        root->subdirs[i]->dname = NULL;
        root->subdirs[i]->next = NULL;
        root->subdirs[i]->corres_dentry = NULL;
    }
    struct dentry *root_self = (struct dentry *)malloc(sizeof(struct dentry));
    root_self->d_sb = sb;
    root_self->parent = NULL;
    root_self->d_time = root->d_time;
    root_self->type = __link;
    strcpy(root_self->d_iname, ".");
    root_self->d_inode = root->d_inode;
    root->d_inode->i_nlink++;
    hash_table_insert(root, root_self);

    unsigned long offset = 0;
    memcpy(sb->s_bdev + offset, &sb->s_blocknumbers, sizeof(unsigned long));
    offset += sizeof(unsigned long);
    memcpy(sb->s_bdev + offset, &sb->s_blocksize, sizeof(unsigned long));
    offset += sizeof(unsigned long);
    memcpy(sb->s_bdev + offset, &sb->s_bitmap_blks, sizeof(int));
    offset += sizeof(int);
//    memcpy(sb->s_bdev + offset, &sb->s_inodes_num, sizeof(unsigned long));
//    offset += sizeof(unsigned long);

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
//        if (sb->s_inodes)
//            inode_list_free(sb->s_inodes);
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

struct super_block *load_block(struct dentry *root) {
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
//    memcpy(&sb->s_inodes_num, sb->s_bdev + offset, sizeof(unsigned long));
//    offset += sizeof(unsigned long);

//    sb->s_inodes = NULL;

    root->parent = NULL;
    root->type = __directory;
    root->d_sb = sb;
    root->d_inode = alloc_inode(sb);
    for (int i = 0; i < HASH_TABLE_ROW; i++) {
        root->subdirs[i] = (struct dir_hash_table *)malloc(sizeof(struct dir_hash_table));
        root->subdirs[i]->dname = NULL;
        root->subdirs[i]->next = NULL;
        root->subdirs[i]->corres_dentry = NULL;
    }
    struct dentry *root_self = (struct dentry *)malloc(sizeof(struct dentry));
    root_self->d_sb = sb;
    root_self->parent = NULL;
    root_self->d_time = root->d_time;
    root_self->type = __link;
    strcpy(root_self->d_iname, ".");
    root_self->d_inode = root->d_inode;
    root->d_inode->i_nlink++;
    hash_table_insert(root, root_self);

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
//    new_inode->i_no = sb->s_inodes_num;

    struct inode_linked_list *ptr = (struct inode_linked_list *)malloc(sizeof(struct inode_linked_list));
    ptr->inode = new_inode;
    ptr->next = NULL;

//    if(sb->s_inodes == NULL) {
//        sb->s_inodes = (struct inode_linked_list *)malloc(sizeof(struct inode_linked_list));
//        sb->s_inodes->inode = NULL;
//        sb->s_inodes->next = NULL;
//    }
//    ptr->next = sb->s_inodes->next;
//    sb->s_inodes->next = ptr;
//    sb->s_inodes_num++;

    return new_inode;
}

bool occupy_block(blkcnt_t blk_no, struct super_block *sb) {
    unsigned long begin_pos = sb->s_blocksize;
    unsigned long char_pos = (blk_no) / 8 + (sb->s_bitmap_blks + 4) / 8 + begin_pos;
    int char_bit = (int)blk_no % 8 ;
    printf("%x\n", ((char *)sb->s_bdev)[char_pos]);
    char *test_char = (char *)sb->s_bdev + char_pos;
    if (test_bit_char(*test_char, 7 - char_bit) == true)
        return false;
    char result = fill_bit_char(*test_char, 7 - char_bit);
    ((char *)sb->s_bdev)[char_pos] = result;
    printf("%x\n", ((char *)sb->s_bdev)[char_pos]);
    return true;
}

bool release_block(blkcnt_t blk_no, struct super_block *sb) {
    unsigned long begin_pos = sb->s_blocksize;
    unsigned long char_pos = (blk_no) / 8 + (sb->s_bitmap_blks + 4) / 8 + begin_pos;
    int char_bit = (int)blk_no % 8 ;
    printf("%x\n", ((char *)sb->s_bdev)[char_pos]);
    char *test_char = (char *)sb->s_bdev + char_pos;
    if (test_bit_char(*test_char, 7 - char_bit) == false)
        return false;
    char result = release_bit_char(*test_char, sizeof(char) - 1 - char_bit);
    ((char *)sb->s_bdev)[char_pos] = result;
    printf("%x\n", ((char *)sb->s_bdev)[char_pos]);
    return true;
}

bool alloc_block_for_inode(struct super_block *sb, struct inode *inode) {
    if (!inode)
        return false;
    if (inode->i_blocks == 0) {
        inode->i_list = (struct blk_lists *) malloc(sizeof(struct blk_lists));
        inode->i_list->blk_len = 0;
        inode->i_list->next_blk = NULL;
        inode->i_nlink = 0;
        inode->i_btyes = 0;
        inode->i_sb = sb;
    }
    unsigned long blk_max_no = sb->s_blocknumbers - sb->s_bitmap_blks;
    unsigned long blk_char_pos = sb->s_blocksize * (sb->s_bitmap_blks + 1);
    for (unsigned long i = 0; i < blk_max_no; i++) {
        if (occupy_block(i, sb)) {
            blk_char_pos = blk_char_pos + i * sb->s_blocksize;
            inode->i_no = i;
            struct blk_lists *ptr = inode->i_list;
            while (ptr->next_blk) {
                ptr = ptr->next_blk;
            }
            ptr->next_blk = sb->s_bdev + blk_char_pos;
            ptr->next_blk->next_blk = NULL;
            inode->i_blocks++;
            return true;
        }
    }
    return false;
}

void *free_block_for_inode(struct super_block *sb, struct inode *inode) {
    if (!inode)
        return NULL;
    unsigned long num = inode->i_blocks;
    if (!inode->i_list) {
        printf("Critical error, the memory be freed is not allocated!\n");
        return NULL;
    }
    struct blk_lists *ptr = inode->i_list, *prev;
    ptr = ptr->next_blk;
    unsigned long blk_max_no = sb->s_blocknumbers - sb->s_bitmap_blks;
    unsigned long blk_char_pos = sb->s_blocksize * (sb->s_bitmap_blks + 1);
    while(ptr) {
        prev = ptr;
        release_block(ptr->blk_no, sb);
        free(prev);
        ptr = ptr->next_blk;
    }
    release_block(inode->i_no, sb);
    inode->i_list = NULL;
    inode->i_sb = NULL;
    free(inode);
    inode = NULL;
    return NULL;
}

void *alloc_data_block(struct super_block *sb) {
    unsigned long blk_max_no = sb->s_blocknumbers - sb->s_bitmap_blks;
    unsigned long blk_char_pos = sb->s_blocksize * (sb->s_bitmap_blks + 1);
    for (unsigned long i = blk_max_no - 1; i >= 0; i++) {
        if (occupy_block(i, sb)) {
            blk_char_pos = blk_char_pos + i * sb->s_blocksize;
            return sb->s_bdev + blk_char_pos;
        }
    }
    return NULL;
}