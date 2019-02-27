//
// Created by 永鑫   徐 on 2019-02-27.
//

#include "../include/trival_helper.h"

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
