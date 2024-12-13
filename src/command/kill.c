#include "stdio.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("kill [error]: you should use kill as following format:\n");
        printf("\tkill [pid]\n");
    } else {

        if (kill(atoi(argv[1])) != 0) {
            printf("Failed to kill %s!\n", argv[1]);
            return 0;
        } else {
            printf("Successfully kill %s!\n", argv[1]);
        }
    }
    return 0;
}

int atoi(char* str) {
    int result = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        result = result * 10 + str[i] - '0';
    }
    return result;
}