#include <stdio.h>
#include "user.h"
#include "super_block.h"

int main(int argc, const char *argv[]) {
    struct super_block *sb = NULL;
    if (argc == 1) {
        sb = load_block();
    }
    else {
        sb = init_block();
    }
    struct user_linked_list *head = load_users_info();

    save_users_info(head);
    free_user_info(head);
    save_block(sb);
    free_block(sb);

    return 0;
}