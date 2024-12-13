#include "stdio.h"

int main(int argc, char* argv[]) {
    struct proc* p = &proc_table[pid];

    if (p->p_flags & FREE_SLOT) {
        disp_color_str("Error: Process not found.\n", MAKE_COLOR(RED, BLACK));
        return;
    }

    // 如果进程正在发送或接收消息，先取消这些操作
    if (p->p_flags & SENDING) {
        p->p_flags &= ~SENDING;  // 清除发送标志
        disp_color_str("Process is sending, operation canceled.\n", MAKE_COLOR(YELLOW, BLACK));
    } else if (p->p_flags & RECEIVING) {
        p->p_flags &= ~RECEIVING;  // 清除接收标志
        disp_color_str("Process is receiving, operation canceled.\n", MAKE_COLOR(YELLOW, BLACK));
    }

    // 如果进程正在等待子进程退出，则设置为HANGING状态
    if (p->p_flags & WAITING) {
        p->p_flags &= ~WAITING;
        p->p_flags |= HANGING;
        disp_color_str("Process is waiting for a child to exit, now in HANGING state.\n", MAKE_COLOR(RED, BLACK));
    }

    // 设置进程为FREE_SLOT状态，表示其已被终止
    p->p_flags = FREE_SLOT;
    disp_color_str("Process terminated successfully.\n", MAKE_COLOR(GREEN, BLACK));
}
