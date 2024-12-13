#include "type.h"
#include "stdio.h"
#include "const.h"
#include "protect.h"
#include "string.h"
#include "fs.h"
#include "proc.h"
#include "tty.h"
#include "console.h"
#include "global.h"
#include "proto.h"

// parameter: path name to search
// return: a buffer that stores the names of files
PUBLIC char* search(char* path) {
    MESSAGE msg;
    msg.type = SEARCH;
    memset(msg.buf, 0, 200);
    memcpy(msg.buf, path, strlen(path));
    send_recv(BOTH, TASK_FS, &msg);
    // printf("msg return: %s\n", msg.buf);
    // printf("msg.buf address: %x\n", msg.buf);
    char* temp = (char*)msg.BUF;
    memcpy(temp, msg.buf, strlen(msg.buf));
    temp[strlen(msg.buf)] = '\0';
    return temp;
}