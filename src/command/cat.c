#include "stdio.h"
#include "string.h"
#include "myelf.h"

int strncmp(char* a, char* b, int n) {
    int i = 0;
    for (i = 0; i < n; i++) {
        if (a[i] != b[i]) {
            return 1;
        }
    }
    return 0;
}

int is_elf(Elf32_Ehdr elf_ehdr) {
    if ((strncmp(elf_ehdr.e_ident, ELFMAG, SELFMAG)) == 0)
        return 1;
    else
        return 0;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
	printf("Usage: cat <filename>\n");
        return 1;
    }
    int fd = open(argv[1], O_RDWR);
    if (fd == -1)
    {
	printf("invalid filename\n");
	return 1;
    }
    Elf32_Ehdr elf_ehdr;
    read(fd, &elf_ehdr, sizeof(elf_ehdr));
    if (is_elf(elf_ehdr))
    {
	printf("cant cover ELF file\n");
    	close(fd);
	return 1;
    }
    close(fd);

    fd = open(argv[1], O_RDWR);
    int bytes_get;
    char buf[128];
    while (bytes_get = read(fd, &buf, sizeof(buf)) != 0)
    {
	printf("%s", buf);
    }
    printf("\n");

    close(fd);
    return 0;
}
