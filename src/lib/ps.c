/*************************************************************************//**
 *****************************************************************************
 * @file   ps.c
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
 *                              psearch
 *****************************************************************************/
/**
 * Search all processes.
 * 
 * @return  Zero if success, otherwise -1.
 *****************************************************************************/

PUBLIC int ps()
{
    MESSAGE msg;
	msg.type = PSEARCH;

	send_recv(BOTH, TASK_MM, &msg);
	assert(msg.type == SYSCALL_RET);
	assert(msg.RETVAL == 0);

	return 0;
}