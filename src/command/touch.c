#include "stdio.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("touch [error]: you should use touch as following format:\n");
        printf("\ttouch [filename] [filename] ...\n");
    } else {
	int i;
        for (i = 1; i < argc; i++) {
            int fd = open(argv[i], O_CREAT);
            if (fd == -1) { // create file failed
                printf("Failed to create file %s!\n", argv[i]);
                return -1;
            } else {
                printf("Successfully create file %s!\n", argv[i]);
            }
        }
    }
    return 0;
}
