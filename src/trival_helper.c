//
// Created by 永鑫   徐 on 2019-02-27.
//

#include "../include/trival_helper.h"

const char char_mask = 0x01;

inline bool test_bit_char(char byte, int num) {
    if (num > (sizeof(char) * 8 - 1) || num < 0)
        return false;
    char test = char_mask << num;
    char test2 = byte & test;
    return ((test2 >> num) & char_mask);
}

inline char fill_bit_char(char byte, int num) {
    if (num > (sizeof(char) * 8 - 1) || num < 0)
        return 0;
    char rtn = byte | (char_mask << num);
    return rtn;
}

inline char release_bit_char(char byte, int num) {
    if (num > (sizeof(char) * 8 - 1) || num < 0)
        return 0;
    char rtn = byte & ~(char_mask << num);
    return rtn;
}

struct tm* get_local_time(void) {
    time_t t;
    struct tm * lt;
    time (&t);
    lt = localtime (&t);
    return lt;
}

void print_time(struct tm* lt) {
    printf ( "%d/%d/%d %d:%d:%d\n",lt->tm_year+1900, lt->tm_mon, lt->tm_mday, lt->tm_hour, lt->tm_min, lt->tm_sec);
}

unsigned int priority_get_by_number(int num) {
    unsigned int rtn = 0;
    int temp = num;
    int residue;
    unsigned int decimal = 0;
    while (temp > 0) {
        residue = temp % 10;
        rtn =  residue << (3 * decimal) & rtn;
        decimal++;
        temp = temp / 10;
    }
    return rtn;
}

