/*************************************************************************//**
 *****************************************************************************
 * @file   ps.c
 *****************************************************************************
 *****************************************************************************/
#include "stdio.h"

int main(int argc, char* argv[]) {
    struct proc* p;
    char info[STR_DEFAULT_LEN];
    
    disp_color_str("PID\tName\tState\n", MAKE_COLOR(GREEN, BLACK));

    for (p = &FIRST_PROC; p <= &LAST_PROC; p++) {
        if (p->p_flags & FREE_SLOT) {
            continue;  // 跳过未使用的进程槽
        }

        // 获取进程的状态
        const char* state = "UNKNOWN";
        if (p->p_flags & SENDING) {
            state = "SENDING";
        } else if (p->p_flags & RECEIVING) {
            state = "RECEIVING";
        } else if (p->p_flags & WAITING) {
            state = "WAITING";
        } else if (p->p_flags & HANGING) {
            state = "HANGING";
        }

        // 打印进程信息
        sprintf(info, "%d\t%s\t%s\n", proc2pid(p), p->name, state);
        disp_color_str(info, MAKE_COLOR(CYAN, BLACK));
    }
}
