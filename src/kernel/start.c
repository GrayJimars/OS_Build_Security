
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                            start.c
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                                                    Forrest Yu, 2005
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

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


/*======================================================================*
                            cstart
 *======================================================================*/
PUBLIC void cstart()
{
	disp_str("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n-----\"cstart\" begins-----\n");

	/* 将 LOADER 中的 GDT 复制到新的 GDT 中 */
	memcpy(	&gdt,				   /* New GDT */
		(void*)(*((u32*)(&gdt_ptr[2]))),   /* Base  of Old GDT */
		*((u16*)(&gdt_ptr[0])) + 1	   /* Limit of Old GDT */
		);
	/* gdt_ptr[6] 共 6 个字节：0~15:Limit  16~47:Base。用作 sgdt 以及 lgdt 的参数。 */
	u16* p_gdt_limit = (u16*)(&gdt_ptr[0]);
	u32* p_gdt_base  = (u32*)(&gdt_ptr[2]);
	*p_gdt_limit = GDT_SIZE * sizeof(struct descriptor) - 1;
	*p_gdt_base  = (u32)&gdt;

	/* idt_ptr[6] 共 6 个字节：0~15:Limit  16~47:Base。用作 sidt 以及 lidt 的参数。 */
	u16* p_idt_limit = (u16*)(&idt_ptr[0]);
	u32* p_idt_base  = (u32*)(&idt_ptr[2]);
	*p_idt_limit = IDT_SIZE * sizeof(struct gate) - 1;
	*p_idt_base  = (u32)&idt;

	init_prot();

	disp_str("-----\"cstart\" finished-----\n");
}

PUBLIC void printBootLogo() {
	disp_str(" ____            _           _          _ \n");      
        disp_str("|  _ \\ _   _ ___| |_ _   _  | |    __ _| | _____ \n");
        disp_str("| |_) | | | / __| __| | | | | |   / _` | |/ / _ \\ \n");
        disp_str("|  _ <| |_| \\__ \\ |_| |_| | | |__| (_| |   <  __/ \n");
        disp_str("|_| \_\\ \\__,_|___/\\__|\\__, | |_____\\__,_|_|\\_\\___| \n");
        disp_str("                     |___/ \n");
	// disp_str("\n-------now here------\n");
}
