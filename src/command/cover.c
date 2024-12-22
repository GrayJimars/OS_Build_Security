#include "stdio.h"
#include "string.h"

void writeEscapeString(int fd, char* string);

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        printf("Usage: cover <filename> <text>\n");
        return 1;
    }
    int fd = open(argv[1], O_RDWR);
    if (fd == -1)
    {
        printf("invalid filename\n");
        return 1;
    }

    writeEscapeString(fd, argv[2]);
    
    close(fd);
    return 0;
}

void writeEscapeString(int fd, char* string)
{
    char* chp;
    for (chp = string;chp < string + strlen(string);chp++)
    {
        if (*chp == '\\')
        {
            chp++;
            switch (*chp)
            {
                case '0':
                    write(fd, "\0", 1);
                    break;
                case 'a':
                    write(fd, "\a", 1);
                    break;
                case '\b':
                    write(fd, "\b", 1);
                    break;
                case 't':
                    write(fd, "\t", 1);
                    break;
                case 'n':
                    write(fd, "\n", 1);
                    break;
                case 'v':
                    write(fd, "\v", 1);
                    break;
                case 'f':
                    write(fd, "\f", 1);
                    break;
                case 'r':
                    write(fd, "\r", 1);
                    break;
                case '\"':
                    write(fd, "\"", 1);
                    break;
                case '\'':
                    write(fd, "\'", 1);
                    break;
                case '\?':
                    write(fd, "\?", 1);
                    break;
                case '\\': 
                    write(fd, "\\", 1);
                    break;
                default:
		    printf("invalid escape char: \\%c", *chp);
                    break;
            }
        }
        else
        {
            write(fd, chp, 1);
        }
    }
}
