//
// Created by 永鑫   徐 on 2019-02-25.
//

#ifndef VFS_DATA_STRUCTURES_H
#define VFS_DATA_STRUCTURES_H

#define USR_NAME_LEN 50
#define PSW_LEN 50

struct user{
    char proirty;
    char name[USR_NAME_LEN];
    char psw[PSW_LEN];
};

#endif //VFS_DATA_STRUCTURES_H
