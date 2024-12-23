/*************************************************************************//**
 *****************************************************************************
 * @file   read.c
 * @brief  read()
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
 *                                read
 *****************************************************************************/
/**
 * Read from a file descriptor.
 * 
 * @param fd     File descriptor.
 * @param buf    Buffer to accept the bytes read.
 * @param count  How many bytes to read.
 * 
 * @return  On success, the number of bytes read are returned.
 *          On error, -1 is returned.
 *****************************************************************************/
PUBLIC int read(int fd, void *buf, int count)
{
	MESSAGE msg,msg_log;
	msg.type = READ;
	msg.FD   = fd;
	msg.BUF  = buf;
	msg.CNT  = count;

	send_recv(BOTH, TASK_FS, &msg);

	msg_log.type = FILE_LOG_READ;
	msg_log.u.m2.m2p2=" Reading file ";
	msg_log.u.m2.m2p3=" fd: ";
    msg_log.u.m1.m1i1=msg.FD;
	msg_log.u.m2.m2p4=buf;
	send_recv(SEND, TASK_LOG, &msg_log);

	return msg.CNT;
}
