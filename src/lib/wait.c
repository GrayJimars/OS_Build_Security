/*************************************************************************//**
 *****************************************************************************
 * @file   wait.c
 * @brief  wait()
 * @author Forrest Y. Yu
 * @date   Tue May 20 01:23:58 2008
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
 *                                wait
 *****************************************************************************/
/**
 * Wait for the child process to terminiate.
 * 
 * @param status  The value returned from the child.
 * 
 * @return  PID of the terminated child.
 *****************************************************************************/
PUBLIC int wait(int * status)
{
	MESSAGE msg,msg_log;
	msg.type   = WAIT;

	send_recv(BOTH, TASK_MM, &msg);

	*status = msg.STATUS;
	msg_log.type=PROC_LOG;
    msg_log.u.m2.m2p2=" Exit Process ";
	msg_log.u.m2.m2p3=" PID : ";
    msg_log.u.m1.m1i1=msg.PID;
	send_recv(SEND, TASK_LOG, &msg_log);  // 发送日志信息给 rsyslog

	return (msg.PID == NO_TASK ? -1 : msg.PID);
}
