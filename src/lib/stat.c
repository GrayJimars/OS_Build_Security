/*************************************************************************//**
 *****************************************************************************
 * @file   stat.c
 * @brief  
 * @author Forrest Y. Yu
 * @date   Wed May 21 21:17:21 2008
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
 *                                stat
 *************************************************************************//**
 * 
 * 
 * @param path 
 * @param buf 
 * 
 * @return  On success, zero is returned. On error, -1 is returned.
 *****************************************************************************/
PUBLIC int stat(const char *path, struct stat *buf)
{
	MESSAGE msg;

	msg.type	= STAT;

	msg.PATHNAME	= (void*)path;
	msg.BUF		= (void*)buf;
	msg.NAME_LEN	= strlen(path);

	send_recv(BOTH, TASK_FS, &msg);
	assert(msg.type == SYSCALL_RET);

	MESSAGE sys_log;
	sys_log.type=SYS_LOG;
	sys_log.u.m2.m2p2=" syscall return from sendrecv for file stat";
	send_recv(SEND, TASK_LOG, &sys_log);
	
	return msg.RETVAL;
}
