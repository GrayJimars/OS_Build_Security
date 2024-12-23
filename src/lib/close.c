/*************************************************************************//**
 *****************************************************************************
 * @file   close.c
 * @brief  
 * @author Forrest Y. Yu
 * @date   Mon Apr 21 17:08:19 2008
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
 *                                close
 *****************************************************************************/
/**
 * Close a file descriptor.
 * 
 * @param fd  File descriptor.
 * 
 * @return Zero if successful, otherwise -1.
 *****************************************************************************/
PUBLIC int close(int fd)
{
	MESSAGE msg,msg_log;
	msg.type   = CLOSE;
	msg.FD     = fd;
	msg_log.type = FILE_LOG_CLOSE;
	msg_log.u.m2.m2p2=" File closed ";
	msg_log.u.m2.m2p3=" fd : ";
    msg_log.u.m1.m1i1=msg.FD;
	send_recv(SEND, TASK_LOG, &msg_log); 

	send_recv(BOTH, TASK_FS, &msg);

	return msg.RETVAL;
}
