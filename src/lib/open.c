/*************************************************************************//**
 *****************************************************************************
 * @file   open.c
 * @brief  open()
 * @author Forrest Y. Yu
 * @date   2008
 *****************************************************************************
 *****************************************************************************/

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

/*****************************************************************************
 *                                open
 *****************************************************************************/
/**
 * open/create a file.
 * 
 * @param pathname  The full path of the file to be opened/created.
 * @param flags     O_CREAT, O_RDWR, etc.
 * 
 * @return File descriptor if successful, otherwise -1.
 *****************************************************************************/
int is_inited = 0;
int list_inited = 0;

PUBLIC int open(const char *pathname, int flags)
{

	MESSAGE msg,msg_log;
	msg.type	= OPEN;
	msg.PATHNAME	= (void*)pathname;
	msg.FLAGS	= flags;
	msg.NAME_LEN	= strlen(pathname);
	if(is_inited)
	{
		printf("%s11\n",pathname);
		int pid = getpid();
		printf("%d\n",pid);
	}

	send_recv(BOTH, TASK_FS, &msg);

	assert(msg.type == SYSCALL_RET);
	msg_log.type = FILE_LOG;
	msg_log.u.m2.m2p2=" Open file ";
	msg_log.u.m2.m2p3=" fd: ";
    msg_log.u.m1.m1i1=msg.FD;
	send_recv(SEND, TASK_LOG, &msg_log); 

	return msg.FD;
}
