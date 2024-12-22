
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                            global.h
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                                                    Forrest Yu, 2005
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/* EXTERN is defined as extern except in global.c */
#ifdef	GLOBAL_VARIABLES_HERE
#undef	EXTERN
#define	EXTERN
#endif


EXTERN	int	ticks;

EXTERN	int	disp_pos;

EXTERN	u8			gdt_ptr[6];	/* 0~15:Limit  16~47:Base */
EXTERN	struct descriptor	gdt[GDT_SIZE];
EXTERN	u8			idt_ptr[6];	/* 0~15:Limit  16~47:Base */
EXTERN	struct gate		idt[IDT_SIZE];

EXTERN	u32	k_reenter;
EXTERN	int	current_console;

EXTERN	int	key_pressed; /**
			      * used for clock_handler
			      * to wake up TASK_TTY when
			      * a key is pressed
			      */

EXTERN	struct tss	tss;
EXTERN	struct proc*	p_proc_ready;

extern	char		task_stack[];
extern	struct proc	proc_table[];
extern  struct task	task_table[];
extern  struct task	user_proc_table[];
extern	irq_handler	irq_table[];
extern	TTY		tty_table[];
extern  CONSOLE		console_table[];

/* MM */
EXTERN	MESSAGE			mm_msg;
extern	u8 *			mmbuf;
extern	const int		MMBUF_SIZE;
EXTERN	int			memory_size;

/* FS */
EXTERN	struct file_desc	f_desc_table[NR_FILE_DESC];
EXTERN	struct inode		inode_table[NR_INODE];
EXTERN	struct super_block	super_block[NR_SUPER_BLOCK];
extern	u8 *			fsbuf;
extern	const int		FSBUF_SIZE;
EXTERN	MESSAGE			fs_msg;
EXTERN	struct proc *		pcaller;
EXTERN	struct inode *		root_inode;
extern	struct dev_drv_map	dd_map[];

/* for test only */
extern	char *			logbuf;
extern	const int		LOGBUF_SIZE;
extern	char *			logdiskbuf;
extern	const int		LOGDISKBUF_SIZE;

extern int is_inited;
PUBLIC struct s_queue queue[3];
#define STATIC_CHECK 1
#define DYNAMIC_CHECK 1

#define Whitelist_max 50
#define FILE_MAX_COUNT 20    // 字符串数量
#define FILE_MAX_LENGTH 20 // 每个字符串的最大长度
struct Whitelist {
    int list[Whitelist_max];
    int tail; 
};

struct protected_filelist {
    char file_list[FILE_MAX_COUNT][FILE_MAX_LENGTH];
    int tail; 
};

extern struct Whitelist open_white_list;
extern struct protected_filelist protected_file;
