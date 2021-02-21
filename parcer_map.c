// #include "includes/cube3d.h"
#include "gnl/get_next_line.h"
#include <fcntl.h>


int parcer_map(int fd)
{
    char *map;

    while (get_next_line(fd, &map) != 0)
    {
        printf("%s\n", map);
    }
}

int main()
{
    int fd;
    fd = open("map.cub", O_RDONLY);
    parcer_map(fd);
}