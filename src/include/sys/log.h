#ifndef _ORANGES_LOG_H_
#define _ORANGES_LOG_H_

// #define TASK_LOG    5  

#define DEV_LOG_ENABLE 1
#define FILE_LOG_ENABLE 1
#define PROC_LOG_ENABLE 1
#define SYS_LOG_ENABLE 1

/* 系统初始化完成标志 */
EXTERN int system_ready;
EXTERN int dev_ready;

// 系统调用日志，最多记录128条
#define MAX_SYSCALL_LOGS 128

struct syscall_log {
    char proc_name[16];    // 进程名
    int pid;               // 进程ID
    char syscall_name[16]; // 系统调用名
    int ret;              // 返回值
    int valid;            // 是否有效
};

EXTERN struct syscall_log syscall_logs[MAX_SYSCALL_LOGS];
EXTERN int syscall_log_index;





#endif