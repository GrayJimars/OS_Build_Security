/*************************************************************************//**
 *****************************************************************************
 * @file   unlink.c
 * @brief  
 * @author Forrest Y. Yu
 * @date   Tue Jun  3 16:12:05 2008
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
 *                                unlink
 *****************************************************************************/
/**
 * Delete a file.
 * 
 * @param pathname  The full path of the file to delete.
 * 
 * @return Zero if successful, otherwise -1.
 *****************************************************************************/
PUBLIC int unlink(const char * pathname)
{
	MESSAGE msg,msg_log;
	msg.type   = UNLINK;

	msg.PATHNAME	= (void*)pathname;
	msg.NAME_LEN	= strlen(pathname);

	send_recv(BOTH, TASK_FS, &msg);

	if(msg.RETVAL == 0)
	{
		msg_log.type = FILE_LOG_DELETE;
		msg_log.u.m2.m2p2=" File delete ";
		msg_log.u.m2.m2p3=" pathname: ";
        msg_log.u.m2.m2p4=pathname;
		send_recv(SEND, TASK_LOG, &msg_log); 
	}

	return msg.RETVAL;
}
