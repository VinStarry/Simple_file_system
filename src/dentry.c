//
// Created by 永鑫   徐 on 2019-02-25.
//

#include "../include/dentry.h"

const char * const dentry_path = "./data/dentry.txt";

bool save_entry(struct dentry *root) {
    FILE *fp = fopen(dentry_path, "w");
    if (fp == NULL) {
        printf("An error occurs when open %s\n, save entry failed!\n", dentry_path);
        return false;
    }
    int level = 0;
    fprintf(fp, "%d\n%lu %c\n", level, root->d_inode->i_no, root->type);
//    fprintf(fp, "%d/%d/%d %d:%d:%d\n",root->d_time->tm_year+1900, root->d_time->tm_mon, root->d_time->tm_mday, root->d_time->tm_hour, root->d_time->tm_min, root->d_time->tm_sec);
    fwrite(root->d_time, sizeof(struct tm), 1, fp);
    fputc('\n', fp);
    fprintf(fp, "%s\n", root->d_iname);
    fclose(fp);
    return true;
}

bool load_entry(struct dentry *root) {
    FILE *fp = fopen(dentry_path, "r");
    if (fp == NULL) {
        printf("An error occurs when open %s\n, load entry failed!\n", dentry_path);
        return false;
    }
    int level = 0;
    fscanf(fp, "%d\n%lu %c\n", &level, &root->d_inode->i_no, &root->type);
    root->d_time = (struct tm *)malloc(sizeof(struct tm));
    fread(root->d_time, sizeof(struct tm), 1, fp);
    fputc('\n', fp);
    fscanf(fp, "%s\n", root->d_iname);
    fclose(fp);
    return true;
}