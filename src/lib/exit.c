/*************************************************************************//**
 *****************************************************************************
 * @file   exit.c
 * @brief  
 * @author Forrest Y. Yu
 * @date   Tue May  6 14:25:33 2008
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
 *                                exit
 *************************************************************************//**
 * Terminate the current process.
 * 
 * @param status  The value returned to the parent.
 *****************************************************************************/
PUBLIC void exit(int status)
{
	MESSAGE msg,msg_log;
	msg.type	= EXIT;
	msg.STATUS	= status;
	msg_log.type=PROC_LOG;
    msg_log.u.m2.m2p2=" Exit Process ";
	msg_log.u.m2.m2p3=" Status : ";
    msg_log.u.m1.m1i1=msg.STATUS;
	send_recv(SEND, TASK_LOG, &msg_log);  // 发送日志信息给 rsyslog

	send_recv(BOTH, TASK_MM, &msg);
	assert(msg.type == SYSCALL_RET);
}
