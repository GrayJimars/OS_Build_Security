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
#include "log.h"

PUBLIC void task_log()
{
	MESSAGE msg;
	char log_buf[4096];
	system_ready = 0;
	dev_ready = 0;

	while (1) 
	{
		send_recv(RECEIVE, ANY, &msg);  
		if(DEV_LOG_ENABLE)
		{
			if (msg.type == DEV_LOG) 
			{
        			char log_message[500];  
        			int len = strlen((char*)msg.u.m2.m2p1);
        			if (len < sizeof(log_message)) 
				   {
            				memcpy(log_message, (char*)msg.u.m2.m2p1, len);
            				log_message[len] = '\0';  
        			}
				else 
				{
        			memcpy(log_message, (char*)msg.u.m2.m2p1, sizeof(log_message) - 1);
        			log_message[sizeof(log_message) - 1] = '\0';
        		}

        			char final_message[1000] = "LOG TYPE: Device initial log and Device Access DETAILS: ";  
        			strcat(final_message, log_message);
 					strcat(final_message, "\n");
        			strcat(log_buf,final_message);
        			
				dev_ready=1;
			}
		}

		if(dev_ready==1&&system_ready==1)
		{
			disklog(log_buf);
			dev_ready=0;
			memset(log_buf,0,sizeof(log_buf));		
		}
		
		if(PROC_LOG_ENABLE)
		{		
			if(msg.type == PROC_LOG)
			{
				system_ready = 1;
				char log_message[50]; 
				sprintf(log_message, "LOG TYPE: Process Monitor DETAILS:%s %s%d\n", msg.u.m2.m2p2, msg.u.m2.m2p3, msg.u.m1.m1i1);
				disklog(log_message);
			}
		}
		
		if(FILE_LOG_ENABLE)
		{
			if(msg.type == FILE_LOG)
			{
				system_ready = 1;
				char log_message[50]; 
				sprintf(log_message,"LOG TYPE: FILE ACCESS DETAILS: %s %s%d\n", msg.u.m2.m2p2,msg.u.m2.m2p3,msg.u.m1.m1i1); 
				disklog(log_message);

			}
		
			if(msg.type == FILE_LOG_DO)
			{
				system_ready = 1;
				char log_message[50]; 
				sprintf(log_message,"LOG TYPE: FILE ACCESS DETAILS: %s %s%d %s\n", msg.u.m2.m2p2, msg.u.m2.m2p3, msg.u.m1.m1i1, msg.u.m2.m2p4); 
		  		disklog(log_message);

			}
	
			if(msg.type == FILE_LOG_DELETE)
			{
				system_ready = 1;
				char log_message[50]; 
				sprintf(log_message,"LOG TYPE: FILE ACCESS DETAILS: %s %s %s\n", msg.u.m2.m2p2, msg.u.m2.m2p3,  msg.u.m2.m2p4); 
				disklog(log_message);
			}
		}

		if(SYS_LOG_ENABLE)
		{
			if(msg.type == SYS_LOG)
			{
				system_ready = 1;
				char log_message[50];
				sprintf(log_message,"LOG TYPE: System Call DETAILS: %d %s\n", msg.u.m1.m1i1, msg.u.m2.m2p2); 
				disklog(log_message);
			}
		}

   	}
}



