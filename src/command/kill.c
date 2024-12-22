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
    if (argc != 2){
	printf("usage: poc [pid]\n");
	return 0;
    }

    MESSAGE msg;
    int i = 0;
    int pid = 0;

    for (i = 0; argv[1][i] != '\0'; i++) {
        pid = pid * 10 + argv[1][i] - '0';
    }

    msg.PID = pid;
    msg.STATUS	= 0;
    msg.type = KILL;
    send_recv(BOTH, TASK_MM, &msg);
    printf("killed\n");
    return 0;
}
