//
// Created by 永鑫   徐 on 2019-02-27.
//

#ifndef VFS_TRIVAL_HELPER_H
#define VFS_TRIVAL_HELPER_H

#include <time.h>
#include <stdio.h>

struct tm* get_local_time(void);
void print_time(struct tm* lt);

#endif //VFS_TRIVAL_HELPER_H
