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

int main(int argc, char* argv[]) {
	printf("hello");
/*
    MESSAGE msg;
    int i = 0;
    int pid = 0;

    for (i = 0; argv[1][i] != '\0'; i++) {
        pid = pid * 10 + argv[1][i] - '0';
    }

    msg.PID = pid;
    msg.type = GET_PROC_KILLED;
    send_recv(BOTH, TASK_SYS, &msg);
*/
}
