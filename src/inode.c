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
