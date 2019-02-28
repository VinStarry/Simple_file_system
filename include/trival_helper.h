//
// Created by 永鑫   徐 on 2019-02-27.
//

#ifndef VFS_TRIVAL_HELPER_H
#define VFS_TRIVAL_HELPER_H

#include <time.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "data_structures.h"

struct tm* get_local_time(void);
void print_time(struct tm* lt);
bool test_bit_char(const har byte, const int num);
char fill_bit_char(char byte, int num);
char release_bit_char(char byte, int num);
unsigned long priority_get_by_number(int num);

#endif //VFS_TRIVAL_HELPER_H
