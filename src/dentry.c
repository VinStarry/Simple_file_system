//
// Created by 永鑫   徐 on 2019-02-25.
//

#include "../include/dentry.h"

const char * const dentry_path = "./data/dentry.txt";

bool save_entry(struct dentry *root, struct super_block *sb) {
    FILE *fp = fopen(dentry_path, "w");
    if (fp == NULL) {
        printf("An error occurs when open %s\n, save entry failed!\n", dentry_path);
        return false;
    }

    queue *q = init_queue();
    enqueue(root, q);
    q->front->aux = 0;
    int last_level = 0;

    struct dentry *cur_entry = root;

    size_t num = 0;

    for (int i = 0; i < HASH_TABLE_ROW; i++) {
        struct dir_hash_table *ptr = cur_entry->subdirs[i];
        while (ptr->next) {
            ptr = ptr->next;
            if (!strcmp(ptr->dname, ".") || !strcmp(ptr->dname, ".."))
                continue;
            num++;
        }
    }

    size_t num_of_first_level = 0;

    while (cur_entry != NULL) {
        struct dentry *temp_save = cur_entry;
        bool found = false;
        for (int i = 0; i < HASH_TABLE_ROW; i++) {
            struct dir_hash_table *ptr = cur_entry->subdirs[i];
            while (ptr->next) {
                ptr = ptr->next;
                if (!strcmp(ptr->dname, ".."))
                    continue;
                if (!strcmp(ptr->dname, "."))
                    continue;
                enqueue(ptr->corres_dentry, q);
                found = true;
                last_level++;
                q->rear->aux = last_level;
                cur_entry = ptr->corres_dentry;
                break;
            }
            if (found == true)
                break;
        }
        if (found == false) {
            cur_entry = temp_save->parent;
            last_level--;
            hash_table_delete(cur_entry, temp_save);
        }
        if (temp_save == root) {
            num_of_first_level++;
            if (num_of_first_level == num)
                break;
        }
    }

    while (!queue_empty(q)) {
        fprintf(fp, "%d\n%lu %c\n", q->front->aux, ((struct dentry *)q->front->val)->d_inode->i_no, ((struct dentry *)q->front->val)->type);

        put_inode_memory_by_num(((struct dentry *)q->front->val)->d_inode, sb);

        fwrite(((struct dentry *)q->front->val)->d_time, sizeof(struct tm), 1, fp);
        fputc('\n', fp);
        fprintf(fp, "%s\n", ((struct dentry *)q->front->val)->d_iname);
        dequeue(q);
    }

    fclose(fp);
    printf("save successfully!\n");
    return true;
}

bool load_entry(struct dentry *root, struct super_block *sb) {
    FILE *fp = fopen(dentry_path, "r");
    if (fp == NULL) {
        printf("An error occurs when open %s\n, load entry failed!\n", dentry_path);
        return false;
    }
    int level = 0;
    if (root->d_inode == NULL) {
        root->d_inode = (struct inode *) malloc(sizeof(struct inode));
    }
    fscanf(fp, "%d\n%lu %c\n", &level, &root->d_inode->i_no, &root->type);

    get_inode_memory_by_num(root->d_inode, sb);

    root->d_time = (struct tm *)malloc(sizeof(struct tm));
    fread(root->d_time, sizeof(struct tm), 1, fp);
    fscanf(fp, "%s\n", root->d_iname);

    queue *q = init_queue();
    enqueue(root, q);
    int last_level = level;
    while (!queue_empty(q)) {
        struct dentry *parent_dir = get_rear_queue(q);
        struct dentry *new_dir = (struct dentry *)malloc(sizeof(struct dentry));
        new_dir->d_inode = (struct inode *)malloc(sizeof(struct inode));
        if (3 != fscanf(fp, "%d\n%lu %c\n", &level, &new_dir->d_inode->i_no, &new_dir->type)) {
            free(new_dir);
            break;
        }
        else {
            get_inode_memory_by_num(new_dir->d_inode, sb);
            new_dir->d_time = (struct tm *)malloc(sizeof(struct tm));
            fread(new_dir->d_time, sizeof(struct tm), 1, fp);
            fscanf(fp, "%s\n", new_dir->d_iname);
            while (level != last_level + 1) {
                dequeue_rear(q);
                last_level--;
            }
            parent_dir = q->rear->val;
            last_level = level;
            enqueue(new_dir, q);
            for (int i = 0; i < HASH_TABLE_ROW; i++) {
                new_dir->subdirs[i] = (struct dir_hash_table *)malloc(sizeof(struct dir_hash_table));
                new_dir->subdirs[i]->dname = NULL;
                new_dir->subdirs[i]->next = NULL;
                new_dir->subdirs[i]->corres_dentry = NULL;
            }

            struct dentry *new_dir_self = (struct dentry *)malloc(sizeof(struct dentry));
            new_dir_self->parent = NULL;
            new_dir_self->d_time = new_dir->d_time;
            new_dir_self->type = __link;
            strcpy(new_dir_self->d_iname, ".");
            new_dir_self->d_inode = new_dir->d_inode;

            new_dir_self->d_inode->i_nlink++;

            hash_table_insert(new_dir, new_dir_self);

            hash_table_insert(parent_dir, new_dir);
            struct dentry *new_dir_parent = (struct dentry *)malloc(sizeof(struct dentry));
            new_dir_parent->parent = NULL;
            new_dir_parent->d_time = parent_dir->d_time;
            new_dir_parent->type = __link;

            strcpy(new_dir_parent->d_iname, "..");
            new_dir_parent->d_inode = parent_dir->d_inode;
            new_dir_parent->d_inode->i_nlink++;

            hash_table_insert(new_dir, new_dir_parent);
        }
    }
    free_queue(&q);

    fclose(fp);
    return true;
}

struct dir_hash_table *d_hash(struct dentry *dentry) {
    struct dir_hash_table *item = (struct dir_hash_table *)malloc(sizeof(struct dir_hash_table));
    item->corres_dentry = dentry;
    item->next = NULL;
    item->dname = (char *)malloc(sizeof(char) * DNAME_LEN);
    strcpy(item->dname, dentry->d_iname);
    size_t len = strlen(item->dname);
    int hash_val = 0;
    for (int i = 0; i < len; i++) {
        hash_val += item->dname[i];
    }
    item->hash_key = hash_val;

    return item;
}

void hash_table_insert(struct dentry *dentry, struct dentry *sub_dentry) {
    struct dir_hash_table *item = d_hash(sub_dentry);
    struct dir_hash_table *ptr = dentry->subdirs[item->hash_key % HASH_TABLE_ROW];
    sub_dentry->parent = dentry;
    item->next = ptr->next;
    ptr->next = item;
}

void hash_table_delete(struct dentry *dentry, struct dentry *sub_dentry) {
    int hash_val = 0;
    size_t len = strlen(sub_dentry->d_iname);
    for (int i = 0; i < len; i++) {
        hash_val += sub_dentry->d_iname[i];
    }
    struct dir_hash_table *ptr = dentry->subdirs[hash_val % HASH_TABLE_ROW];
    while (ptr->next) {
        if (!strcmp(ptr->next->dname, sub_dentry->d_iname)) {
            free(ptr->next->dname);
            struct dir_hash_table *temp = ptr->next;
            ptr->next = ptr->next->next;
            free(temp);
            temp = NULL;
            break;
        }
        ptr = ptr->next;
    }
}

struct dentry *search_by_str(struct dentry *current_dentry, const char *dname) {
    struct dentry *dir = NULL;
    int hash_value = 0;
    size_t len = strlen(dname);
    for (int i = 0; i < len; i++) {
        hash_value += dname[i];
    }
    struct dir_hash_table *ptr = current_dentry->subdirs[hash_value % HASH_TABLE_ROW];
    while (ptr->next) {
        ptr = ptr->next;
        if (!strcmp(ptr->dname, dname)) {
            dir = ptr->corres_dentry;
            return dir;
        }
    }
    return NULL;
}

void packet_user_dlist(dlist *dl, struct user_linked_list *head, struct dentry *root) {
    struct user_linked_list *ptr = head;
    if (head->next) {
        ptr = head->next;
        insert_dlist(dl, root);
    }
    struct dentry *temp = root;
    temp = search_by_str(temp, "home");
    while (ptr->next) {
        ptr = ptr->next;
        temp = search_by_str(temp, ptr->name);
        if (temp)
            insert_dlist(dl, temp);
        else {
            printf("Serious bug! cannot get user %s's home dir\n", ptr->name);
            break;
        }
        temp = temp->parent;
    }
}

struct dentry *change_home_dir(dlist *dl, struct usr_ptr *current_user) {
    return look_up_dlist(dl, current_user->name);
}

void get_current_path_str(struct dentry *dentry, char *str) {
    queue *q = init_queue();
    struct dentry *temp = dentry;
    while (temp != NULL && (0 != strcmp(temp->d_iname, "/")) ) {
        enqueue(temp->d_iname, q);
        temp = temp->parent;
    }
    int i = 0;
    strcpy(str, "/");
    while (!queue_empty(q)) {
        char *tmp_str = dequeue_rear(q);
        strcat(str, tmp_str);
        if (queue_empty(q)) {
            strcat(str, " ");
            break;
        }
        else {
            strcat(str, "/");
        }
    }
    printf("\x1b[34m""%s""\x1b[32m""$""\x1b[0m", str);
}

queue *init_queue(void) {
    queue *q = (queue *)malloc(sizeof(queue));
    q->front = NULL;
    q->rear = NULL;
    q->size = 0;
    return q;
}

/*
 * destroy the whole queue, free memory allocated
 */
queue *free_queue(queue **q) {
    while ((*q)->front != NULL) {
        qnode *temp = (*q)->front;
        (*q)->front = (*q)->front->next;
        temp = NULL;
    }
    (*q)->front = NULL;
    (*q)->rear = NULL;
    (*q)->size = 0;
    free(*q);
    (*q) = NULL;
    return NULL;
}

/*
 * return the value of the front of the queue, return NULL if val is null or queue is empty
 */
qtype get_front_queue(const queue * q) {
    if (q->front)
        return q->front->val;
    else
        return NULL;
}

/*
 * return the value of the rear of the queue, return NULL if val is null or queue is empty
 */
qtype get_rear_queue(const queue * q) {
    if (q->rear)
        return q->rear->val;
    else
        return NULL;
}

/*
 * return true if the queue is empty, false otherwise
 */
bool queue_empty(const queue * q) {
    return !(q->size);
}

/*
 * enqueue a item, return false if overflow
 */
bool enqueue(qtype item, queue *q) {
    if(q->front == NULL) {
        qnode *node = (qnode *)malloc(sizeof(qnode));
        if (node == NULL)
            return false;
        node->val = item;
        node->next = NULL;
        q->front = node;
        q->rear = node;
        q->size = 1;
    }
    else {
        qnode *node = (qnode *)malloc(sizeof(qnode));
        if (node == NULL)
            return false;
        q->rear->next = node;
        node->next = NULL;
        node->val = item;
        q->rear = node;
        q->size++;
    }
    return true;
}

/*
 * dequeue the front of the queue, return NULL if the queue is an empty queue
 */
qtype dequeue(queue *q) {
    if (q->size == 0)
        return NULL;
    qtype rtn = q->front->val;
    if (q->front->next == NULL) {
        q->front = NULL;
        q->rear = NULL;
        q->size = 0;
    }
    else {
        qnode *temp = q->front->next;
        q->front = temp;
        q->size--;
    }
    return rtn;
}

/*
 * dequeue the rear of the queue, return NULL if the queue is an empty queue
 */
qtype dequeue_rear(queue *q) {
    if (q->size == 0)
        return NULL;
    qtype rtn = q->rear->val;
    qnode *t = q->front;
    if (q->rear->val == q->front->val) {
        q->rear = NULL;
        q->front = NULL;
    }
    else {
        while (t->next != q->rear) {
            t = t->next;
        }
        t->next = NULL;
        q->rear = t;
    }
    q->size--;
    return rtn;
}

/*
 * return the size of the queue
 */
size_t get_size_of_queue(const queue * q) {
    return q->size;
}

/*
 * print all elements in queue
 */
void print_queue(const queue * q) {
    qnode *temp = q->front;
    while (temp) {
        if (temp->next)
            printf("%s --> ", (char *)temp->val);
        else
            printf("%s\n", (char *)temp->val);
        temp = temp->next;
    }
}

queue *resolve_path_to_queue(const char * const path) {
    queue *q = init_queue();
    int left_slash_pos = -1;
    for (int i = 0; i < strlen(path); i++) {
        if ( i == 0 && path[i] == '/' ) {
            if (path[1] == '/') {
                // invalid path
                free_queue(&q);
                return NULL;
            }
            enqueue("/", q);
            left_slash_pos = 0;
        }
        else if (i == strlen(path) - 1 && path[i] != '/') {
            i = i + 1;
            char *temp = (char *)malloc(sizeof(char) * (i - left_slash_pos));
            if (temp == NULL) {
                free_queue(&q);
                return NULL;
            }
            for (int j = 0; j < i - left_slash_pos - 1; j++)
                temp[j] = path[left_slash_pos + 1 + j];
            temp[i - left_slash_pos - 1] = '\0';
            enqueue(temp, q);
        }
        else if (path[i] != '/')
            continue;
        else {
            // path[i] == '/'
            if (path[i + 1] == '/') {
                // invalid path
                free_queue(&q);
                return NULL;
            }
            else {
                char *temp = (char *)malloc(sizeof(char) * (i - left_slash_pos));
                if (temp == NULL) {
                    free_queue(&q);
                    return NULL;
                }
                for (int j = 0; j < i - left_slash_pos - 1; j++)
                    temp[j] = path[left_slash_pos + 1 + j];
                temp[i - left_slash_pos - 1] = '\0';
                enqueue(temp, q);
                left_slash_pos = i;
            }
        }
    }
    print_queue(q);
    return q;
}

dlist *init_dlist(void) {
    dlist *dl = (dlist *)malloc(sizeof(dlist));
    dl->next = NULL;
    dl->dir = NULL;
    return dl;
}

void insert_dlist(dlist *dl, struct dentry *dentry) {
    dlist *temp = dl;
    while(temp->next) {
        temp = temp->next;
    }
    temp->next = (dlist *)malloc(sizeof(dlist));
    temp = temp->next;
    temp->dir = dentry;
    temp->next = NULL;
}

void free_dlist(dlist **dl) {
    dlist *tmp = *dl;
    dlist *prev = *dl;

    while (tmp) {
        prev = tmp;
        tmp = tmp->next;
        free(prev);
    }
    tmp = NULL;
    *dl = NULL;
}

void print_dlist(dlist *dl) {
    dlist *temp = dl;
    while(temp->next) {
        temp = temp->next;
        printf("%s\t", temp->dir->d_iname);
    }
    putchar('\n');
}

struct dentry *look_up_dlist(dlist *dl, const char *name) {
    struct dentry *rtn = NULL;
    dlist *temp = dl;
    while(temp->next) {
        temp = temp->next;
        if (!strcmp(name, temp->dir->d_iname) || (!strcmp(name, "root") && !strcmp(temp->dir->d_iname, "/"))) {
            rtn = temp->dir;
            break;
        }
    }
    return rtn;
}