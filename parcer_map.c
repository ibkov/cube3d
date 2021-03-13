#include "includes/cube3d.h"
#include "libft/libft.h"
#include "gnl/get_next_line.h"
#include <fcntl.h>
#include <stdio.h>


// void leave_spaces(char *line)
// {
    
// }

int parse_line(char *line_map)
{
int w;

w = ft_strlen(line_map);
while (line_map[w])
     w++;
return (w);
}

int  parcer_map(char *file_name, pos_gamer *pos)
{
    
    char *line_map;
    int i;
    int j;
    int w;
    int h;
    int fd; 

    h = 1;
    fd = open(file_name, O_RDONLY);
    while (get_next_line(fd, &line_map) != 0)
    {
        w = 0; 
        if ((w = parse_line(line_map)) == -1)
            return (-1);
       
        h++;
    }
    pos->worldMap = (int**)malloc(sizeof(int*) * h);
    i = 0;
    while(i <= h)
    {
        pos->worldMap[i] = (int*)malloc(sizeof(int) * w);
        i++;
    }
    i = 0;
    j = 0;
    close(fd);
    fd = open(file_name, O_RDONLY);
    while (get_next_line(fd, &line_map) != 0)
    {
        i = 0;
        while (line_map[i] && i < w)
        { 
            pos->worldMap[j][i] = (line_map[i] - 48);
            i++;  
            
        }
        if (j < h)
            j++;   
            
    }
    i= 0;
    while (line_map[i])
        {
            pos->worldMap[j][i] = (line_map[i] - 48);
            i++;
        }
        return (1);
}