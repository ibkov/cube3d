#include "includes/cube3d.h"
#include "gnl/get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

// static int		check_map_norme(
// 	t_window *win_infos,
// 	char **map
// )
// {
// 	int x;
// 	int y;

// 	if (!*map || !**map)
// 		return (ERROR);
// 	y = 0;
// 	while (y < win_infos->map->height)
// 	{
// 		x = 0;
// 		if (ft_strlen(map[y]) != (size_t)win_infos->map->width)
// 			return (ERROR);
// 		while (x < win_infos->map->width)
// 		{
// 			if ((y == 0 && map[y][x] != '1')
// 			|| (y == win_infos->map->height - 1 && map[y][x] != '1')
// 			|| (x == 0 && map[y][x] != '1')
// 			|| (x == win_infos->map->width - 1 && map[y][x] != '1'))
// 				return (ERROR);
// 			if (map[y][x] != '0' && map[y][x] != '1' && map[y][x] != '2')
// 				return (ERROR);
// 			x++;
// 		}
// 		y++;
// 	}
// 	return (SUCCES);
// }

// static void		get_map_size(
// 	char *str,
// 	t_window *win_infos)
// {
// 	int i;
// 	int j;
// 	int	width;
// 	int	height;

// 	i = 0;
// 	j = 0;
// 	width = 0;
// 	height = 0;
// 	while (str[i] != '\n')
// 	{
// 		if (!is_whitespace(str[i]))
// 			width++;
// 		i++;
// 	}
// 	win_infos->map->width = width;
// 	while (str[j] != '\0')
// 	{
// 		if (str[j] == '\n')
// 			height++;
// 		j++;
// 		if (str[j] == '\0' && (j > 0 && str[j - 1] != '\n'))
// 			height++;
// 	}
// 	win_infos->map->height = height;
// }

// static char		**malloc_map(
// 	t_window *win_infos)
// {
// 	int		i;
// 	char	**map;

// 	if (!(map = (char **)malloc(sizeof(char *) * win_infos->map->height)))
// 		leave(1, win_infos, "Error\nDuring map malloc");
// 	ft_bzero(map, sizeof(char *) * win_infos->map->height);
// 	i = 0;
// 	while (i < win_infos->map->height)
// 	{
// 		if (!(map[i] = (char *)malloc(sizeof(char) * win_infos->map->width)))
// 			leave(1, win_infos, "Error\nDuring map line malloc");
// 		ft_bzero(map[i], sizeof(char) * win_infos->map->width);
// 		i++;
// 	}
// 	return (map);
// }

// static char		**init_map(
// 	char *str,
// 	char **map,
// 	t_window *win_infos)
// {
// 	int cursor;
// 	int u;
// 	int i;

// 	u = 0;
// 	i = 0;
// 	while (u < win_infos->map->height)
// 	{
// 		cursor = 0;
// 		while (str[i] && str[i] != '\n')
// 		{
// 			if (!is_whitespace(str[i]))
// 				map[u][cursor++] = str[i];
// 			if (str[i] == 'N' || str[i] == 'S' ||
// 				str[i] == 'W' || str[i] == 'E')
// 			{
// 				set_start_pos(win_infos, str[i], cursor, u);
// 				map[u][cursor - 1] = '0';
// 			}
// 			i++;
// 		}
// 		map[u++][cursor] = '\0';
// 		i += 1;
// 	}
// 	return (map);
// }

// char			**map_from_string(
// 	char *str,
// 	t_window *win_infos)
// {
// 	char	**map;

// 	get_map_size(str, win_infos);
// 	map = malloc_map(win_infos);
// 	map = init_map(str, map, win_infos);
// 	if (!check_map_norme(win_infos, map))
// 		leave(1, win_infos, "Error\nIn map format");
// 	if (win_infos->player->posx == -20.0 || win_infos->player->posy == -20.0
// 		|| win_infos->player->dir_x == -20.0
// 		|| win_infos->player->dir_y == -20.0)
// 		leave(1, win_infos, "Player pos/dir did'nt set");
// 	free(str);
// 	return (map);
// }

void parcer_map(char *file_name, pos_gamer *pos)
{
    
    char *line_map;
    int i;
    int j;
    int w;
    int h;
    int fd;

    h = 0;
    fd = open(file_name, O_RDONLY);
    while (get_next_line(fd, &line_map) != 0)
    {
        
        w = 0; 
        while (line_map[w])
            w++;
        h++;
    }
    h += 1;
    ft_putstr_fd("h" ,1);
    ft_putchar_fd(*ft_itoa(h), 1);
    ft_putstr_fd("\nw" ,1);
    ft_putchar_fd(*ft_itoa(w), 1);
    pos->worldMap = (int**)malloc(sizeof(int*) * h);
    i = 0;
    while(i < w)
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
        while (line_map[i])
        {
            pos->worldMap[j][i] = (line_map[i] - 48);
            i++;    
        }
        j++;   
    }
    i= 0;
    ft_putstr_fd(line_map, 1);
    while (line_map[i])
        {
            ft_putchar_fd(line_map[i], 1);
            pos->worldMap[j][i] = (line_map[i] - 48);
            i++;
        }
}