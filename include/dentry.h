//
// Created by 永鑫   徐 on 2019-02-25.
//

#ifndef VFS_DENTRY_H
#define VFS_DENTRY_H

typedef void * qtype;
#include "data_structures.h"
#include "inode.h"

typedef struct _queue_node {
    qtype val;                  // value of the node
    int aux;                    // auxiliary info
    struct _queue_node *next;   // next the node
}qnode;

typedef struct _simple_queue {
    size_t size;    // number of nodes of the queue
    qnode *front;   // front of the queue
    qnode *rear;    // rear of the queue
}queue;

struct __dentry_with_level {
    struct dentry *dir;
    int level;
};

bool save_entry(struct dentry *root, struct super_block *sb);
bool load_entry(struct dentry *root, struct super_block *sb);
struct dir_hash_table *d_hash(struct dentry *dentry);
void hash_table_insert(struct dentry *dentry, struct dentry *sub_dentry);
void hash_table_delete(struct dentry *dentry, struct dentry *sub_dentry);
struct dentry *search_by_str(struct dentry *current_dentry, const char *dname);
void packet_user_dlist(dlist *dl, struct user_linked_list *head, struct dentry *root);
struct dentry *change_home_dir(dlist *dl, struct usr_ptr *current_user);
void get_current_path_str(struct dentry *dentry, char *str);
void travel_dentry(queue *q, slist *str_list, struct dentry *begin_dentry, size_t num);

// initialize queue, allocate memory, return the initialized queue pointer
queue *init_queue(void);
// destroy the whole queue, free memory allocated, return null pointer
queue *free_queue(queue **q);
// return value of the front of the queue, return NULL if val is null or queue is empty
qtype get_front_queue(const queue *q);
// return value of the rear of the queue, return NULL if val is null or queue is empty
qtype get_rear_queue(const queue *q);
// return true if the queue is empty, false otherwise
bool queue_empty(const queue *q);
// enqueue a item, return false if overflow
bool enqueue(qtype item, queue *q);
// dequeue the front of the queue, return NULL if the queue is empty or val is null
qtype dequeue(queue *q);
// dequeue the rear of the queue, return NULL if the queue is empty or val is null
qtype dequeue_rear(queue *q);
// return the size of the queue
size_t get_size_of_queue(const queue *q);
// print_queue, used for debugging
void print_queue(const queue *q);

/*
 * resolve path into a queue
 * example: resolve "../user1/project/foo/main.c"
 * into: ".." --> "user1" --> "project" --> "foo" --> "main.c"
 * where ".." is the front of the queue, and "main.c" is the rear
 */

// resolve path into a queue, return NULL if the path is invalid
queue *resolve_path_to_queue(const char *path);

dlist *init_dlist(void);
void insert_dlist(dlist *dl, struct dentry *dentry);
void free_dlist(dlist **dl);
void print_dlist(dlist *dl);
struct dentry *look_up_dlist(dlist *dl, const char *name);

#endif //VFS_DENTRY_H
