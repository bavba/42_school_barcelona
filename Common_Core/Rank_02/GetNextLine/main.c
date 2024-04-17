#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h> 

int main(int argc, char **argv)
{
    int fd;
    char *line;

    if (argc != 2)
    {
        printf("Usage: %s [file.txt]\n", argv[0]);
        return 1;
    }

    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening the file");
        return 1;
    }

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("Line: %s\n", line);
        free(line);
    }

    close(fd);
    return 0;
}