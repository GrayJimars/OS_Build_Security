#include "type.h"
#include "stdio.h"
#include "string.h"
#include "sys/const.h"
#include "sys/protect.h"
#include "sys/fs.h"
#include "sys/proc.h"
#include "sys/tty.h"
#include "sys/console.h"
#include "sys/global.h"
#include "sys/proto.h"

int int_to_str(int num, char *str) {
    int i = 0, j, temp;
    int is_negative = 0;

    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return i;
    }

    if (num < 0) {
        is_negative = 1;
        num = -num;
    }

    // 处理每一位数字
    while (num > 0) {
        str[i++] = (num % 10) + '0';
        num /= 10;
    }

    if (is_negative) {
        str[i++] = '-';
    }

    // 反转字符串
    for (j = 0; j < i / 2; j++) {
        temp = str[j];
        str[j] = str[i - j - 1];
        str[i - j - 1] = temp;
    }

    str[i] = '\0';
    return i;
}

int main(int argc, char* argv[]) {
    struct proc *p;
    char pidstr[16];
    printf("PID\tNAME\tSTATUS\n");
    int i, len;
    for (i = 0; i < NR_TASKS + NR_PROCS; i++) {
        p = getpaddr(i);
        if (p->p_flags != FREE_SLOT) {
		len = int_to_str(i, pidstr);
		write(1, pidstr, len);
		write(1, "\t", 1);
		write(1, p->name, strlen(p->name));
		write(1, "\t", 1);
            if (p->p_flags == SENDING) {
		write(1, "SENDING\n", 8);
            } else if (p->p_flags == RECEIVING) {
		write(1, "RECEIVING\n", 10);
            } else if (p->p_flags == WAITING) {
		write(1, "WAITING\n", 8);
            } else if (p->p_flags == HANGING) {
		write(1, "HANGING\n", 8);
            } else if (p->p_flags == 0) {
		write(1, "RUNNING\n", 8);
	    } else {
		write(1, "UNKNOW\n", 7);
            }
        }
    }
    return 0;
}
