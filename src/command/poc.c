#include "type.h"
#include "stdio.h"
#include "string.h"
#include "sys/const.h"
#include "sys/protect.h"
#include "sys/fs.h"
#include "sys/proc.h"
#include "sys/tty.h"
#include "sys/console.h"
#include "sys/global.h"
#include "sys/proto.h"


void input(char *p) {
    int i = 0x11223344;
    char buf[8] = "1234567";
    __asm__ __volatile__("xchg %bx, %bx");
    // *buf = 'A';
    // printf("%d", buf);
    char payload[] = {
        0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41,
        0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41,
        0x41, 0x41, 0x41, 0x41, *p, *(p+1), *(p+2),*(p+3)};  // printf("%s\n", buf);
    strcpy(buf, payload);
    printf("%s", buf);
    __asm__ __volatile__("xchg %bx, %bx");
    return;
}

void shellcode() {
    __asm__ __volatile__("xchg %bx, %bx");
    printf("=>\n");
    int i = 10000;
    while (i--)
        ;
    exit(0);
}

int main(int argc, char* argv[]) {
    void (*funcPtr)() = shellcode;
    printf("%d\n",(char*)funcPtr);
    __asm__ __volatile__("xchg %bx, %bx");
    //shellcode();
    input((char*)&funcPtr);
    return 0;
}
