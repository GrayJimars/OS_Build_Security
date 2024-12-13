/*************************************************************************//**
 *****************************************************************************
 * @file   pskill.c
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
#include "keyboard.h"
#include "proto.h"

/*****************************************************************************
 *                                do_psearch
 *****************************************************************************/
/**
 * Search all processes.
 * 
 * @return  Zero if success, otherwise -1.
 *****************************************************************************/
PUBLIC int do_psearch()
{
    struct proc* p;
    char info[STR_DEFAULT_LEN];
    
    disp_color_str("PID\tName\tState\n", MAKE_COLOR(GREEN, BLACK));

    for (p = &FIRST_PROC; p <= &LAST_PROC; p++) {
        if (p->p_flags & FREE_SLOT) {
            continue;  // 跳过未使用的进程槽
        }

        // 获取进程的状态
        const char* state = "UNKNOWN";
        if (p->p_flags & SENDING) {
            state = "SENDING";
        } else if (p->p_flags & RECEIVING) {
            state = "RECEIVING";
        } else if (p->p_flags & WAITING) {
            state = "WAITING";
        } else if (p->p_flags & HANGING) {
            state = "HANGING";
        }

        // 打印进程信息
        sprintf(info, "%d\t%s\t%s\n", proc2pid(p), p->name, state);
        disp_color_str(info, MAKE_COLOR(BLUE, BLACK));
    }

    return 0;
}

/*****************************************************************************
 *                                do_kill
 *****************************************************************************/
/**
 * Kill a process.
 * 
 * @return  Zero if success, otherwise -1.
 *****************************************************************************/
PUBLIC void do_kill()
{
	int i;
	int pid = mm_msg.PID;
	int parent_pid = proc_table[pid].p_parent;
	struct proc * p = &proc_table[pid];

	/* tell FS, see fs_exit() */
	MESSAGE msg2fs;
	msg2fs.type = EXIT;
	msg2fs.PID = pid;
	send_recv(BOTH, TASK_FS, &msg2fs);

	free_mem(pid);

	p->exit_status = 0;

	if (proc_table[parent_pid].p_flags & WAITING) { /* parent is waiting */
		proc_table[parent_pid].p_flags &= ~WAITING;
		cleanup(&proc_table[pid]);
	}
	else { /* parent is not waiting */
		proc_table[pid].p_flags |= HANGING;
	}

	/* if the proc has any child, make INIT the new parent */
	for (i = 0; i < NR_TASKS + NR_PROCS; i++) {
		if (proc_table[i].p_parent == pid) { /* is a child */
			proc_table[i].p_parent = INIT;
			if ((proc_table[INIT].p_flags & WAITING) &&
			    (proc_table[i].p_flags & HANGING)) {
				proc_table[INIT].p_flags &= ~WAITING;
				cleanup(&proc_table[i]);
			}
		}
	}

    return 0;
}

/*****************************************************************************
 *                                cleanup
 *****************************************************************************/
/**
 * Do the last jobs to clean up a proc thoroughly:
 *     - Send proc's parent a message to unblock it, and
 *     - release proc's proc_table[] entry
 * 
 * @param proc  Process to clean up.
 *****************************************************************************/
PRIVATE void cleanup(struct proc * proc)
{
	MESSAGE msg2parent;
	msg2parent.type = SYSCALL_RET;
	msg2parent.PID = proc2pid(proc);
	msg2parent.STATUS = proc->exit_status;
	send_recv(SEND, proc->p_parent, &msg2parent);

	proc->p_flags = FREE_SLOT;
}