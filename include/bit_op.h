//
// Created by 永鑫   徐 on 2019-02-26.
//

#ifndef VFS_BIT_OP_H
#define VFS_BIT_OP_H

#include <stdbool.h>

const char char_mask = 0x01;

inline bool test_bit_char(char byte, int num) {
    if (num > (sizeof(char) * 8 - 1) || num < 0)
        return false;
    return ((byte & (char_mask << num)) >> num);
}

inline char fill_bit_char(char byte, int num) {
    if (num > (sizeof(char) * 8 - 1) || num < 0)
        return false;
    char rtn = byte & (char_mask << num);
    return rtn;
}

#endif //VFS_BIT_OP_H
