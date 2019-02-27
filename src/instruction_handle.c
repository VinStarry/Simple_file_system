//
// Created by 永鑫   徐 on 2019-02-27.
//

#include "../include/instruction_handle.h"

instr_type raw_instruction_handle(char instr[INSTR_MAX_LEN]) {
    instr_type rtn;
    if (!strcmp(instr, "shutdown"))
        rtn = __shutdown;
    else if (!strcmp(instr, "su"))
        rtn = __swap_user;
    else if (!strcmp(instr, "ls"))
        rtn = __list_file;
    else if (!strcmp(instr, "cp"))
        rtn = __copy_file;
    else if (!strcmp(instr, "ln"))
        rtn = __hard_link;
    else if (!strcmp(instr, "cd"))
        rtn = __change_directory;
    else if (!strcmp(instr, "mv"))
        rtn = __move_file;
    else if (!strcmp(instr, "rm"))
        rtn = __remove_file;
    else if (!strcmp(instr, "edit"))
        rtn = __edit_file;
    else if (!strcmp(instr, "clear"))
        rtn = __stdout_clear;
    else
        rtn = __error_instr;
    return rtn;
}
