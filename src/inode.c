//
// Created by 永鑫   徐 on 2019-02-25.
//

#include "../include/inode.h"

struct inode_linked_list *init_inode_list(size_t num, struct super_block *sb) {
    struct inode_linked_list *head = (struct inode_linked_list *)malloc(sizeof(struct inode_linked_list));
    head->next = NULL;
    head->inode = NULL;
    struct inode_linked_list *ptr = head;
    for (size_t i = 0; i < num; i++) {
        ptr->next = (struct inode_linked_list *)malloc(sizeof(struct inode_linked_list));
        ptr = ptr->next;
        ptr->next = NULL;
        ptr->inode = (struct inode *)malloc(sizeof(struct inode));
        ptr->inode->i_no = i;
        ptr->inode->i_sb = sb;
        ptr->inode->i_btyes = 0;
        ptr->inode->i_blocks = 0;
    }
    return head;
}

struct inode_linked_list *inode_list_free(struct inode_linked_list *ilist) {
    if (!ilist)
        return NULL;
    while (ilist) {
        struct inode_linked_list *temp = ilist;
        ilist = ilist->next;
        free(temp->inode);
        free(temp);
    }
    return NULL;
}

void get_inode_memory_by_num(struct inode *inode, struct super_block *sb) {
    unsigned long ino = inode->i_no;
    unsigned long begin_pos = (sb->s_bitmap_blks + 1) * sb->s_blocksize + ino * (sizeof(struct inode));
    unsigned long offset = 0;
    memcpy(&inode->i_uid, sb->s_bdev + begin_pos + offset, sizeof(unsigned long));
    offset += sizeof(unsigned long);
    memcpy(&inode->i_no, sb->s_bdev + begin_pos + offset, sizeof(unsigned long));
    offset += sizeof(unsigned long);
    memcpy(&inode->i_btyes, sb->s_bdev + begin_pos + offset, sizeof(unsigned long));
    offset += sizeof(unsigned long);
    memcpy(&inode->i_nlink, sb->s_bdev + begin_pos + offset, sizeof(unsigned long));
    offset += sizeof(unsigned long);
    memcpy(&inode->mode, sb->s_bdev + begin_pos + offset, sizeof(unsigned long));
    offset += sizeof(unsigned long);
    memcpy(&inode->i_blocks, sb->s_bdev + begin_pos + offset, sizeof(unsigned long));
    offset += sizeof(unsigned long);

}

void put_inode_memory_by_num(struct inode *inode, struct super_block *sb) {
    unsigned long ino = inode->i_no;
    unsigned long begin_pos = (sb->s_bitmap_blks + 1) * sb->s_blocksize + ino * (sizeof(struct inode));
    unsigned long offset = 0;
    memcpy(sb->s_bdev + begin_pos + offset, &inode->i_uid, sizeof(unsigned long));
    offset += sizeof(unsigned long);
    memcpy(sb->s_bdev + begin_pos + offset, &inode->i_no, sizeof(unsigned long));
    offset += sizeof(unsigned long);
    memcpy(sb->s_bdev + begin_pos + offset, &inode->i_btyes, sizeof(unsigned long));
    offset += sizeof(unsigned long);
    memcpy(sb->s_bdev + begin_pos + offset, &inode->i_nlink, sizeof(unsigned long));
    offset += sizeof(unsigned long);
    memcpy(sb->s_bdev + begin_pos + offset, &inode->mode, sizeof(unsigned long));
    offset += sizeof(unsigned long);
    memcpy(sb->s_bdev + begin_pos + offset, &inode->i_blocks, sizeof(unsigned long));
    offset += sizeof(unsigned long);

    fill_block_by_inode_num(inode->i_no, sb);
}

bool test_block_free_by_inode_num(unsigned long inode_num, struct super_block *sb) {
    unsigned long begin_pos = sb->s_blocksize;
    unsigned long char_pos = (inode_num) / 8 + (sb->s_bitmap_blks + 4) / 8 + begin_pos;
    int char_bit = (int)inode_num % 8 ;
//    printf("%x\n", ((char *)sb->s_bdev)[char_pos]);
    char *test_char = (char *)sb->s_bdev + char_pos;
    if (test_bit_char(*test_char, 7 - char_bit) == true)
        return false;   // occupied
    return true;    // free
}

void fill_block_by_inode_num(unsigned long inode_num, struct super_block *sb) {
    unsigned long begin_pos = sb->s_blocksize;
    unsigned long char_pos = (inode_num) / 8 + (sb->s_bitmap_blks + 4) / 8 + begin_pos;
    int char_bit = (int)inode_num % 8 ;
//    printf("%x\n", ((char *)sb->s_bdev)[char_pos]);
    char *test_char = (char *)sb->s_bdev + char_pos;
    char result = fill_bit_char(*test_char, 7 - char_bit);
    ((char *)sb->s_bdev)[char_pos] = result;
}