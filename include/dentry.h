//
// Created by 永鑫   徐 on 2019-02-25.
//

#ifndef VFS_DENTRY_H
#define VFS_DENTRY_H

#include "data_structures.h"

bool save_entry(struct dentry *root);
bool load_entry(struct dentry *root);

#endif //VFS_DENTRY_H
