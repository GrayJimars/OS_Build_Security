
#include "stdio.h"

// command rm call unlink directly to remove the file(argv[1~argc-1])
// and support multi files removing
int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("rm [error]: you should use rm as following format:\n");
        printf("\trm [filename] [filename] ...\n");
    } else {
        for (int i = 1; i < argc; i++) {
            if (unlink(argv[i]) == -1) {
                printf("Failed to remove file %s!\n", argv[i]);
                return -1;
            } else {
                printf("Successfully remove file %s!\n", argv[i]);
            }
        }
    }
    return 0;
}
