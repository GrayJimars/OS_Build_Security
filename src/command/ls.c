#include "stdio.h"

int main(int argc, char* argv[]) {
    if (argc > 1) {
        printf("argc = %d, ", argc);
        printf("too many arguments!\n");
        return -1;
    } else {
        printf("%s\n", search("/"));
        return 0;
    }
}
