
# include "includes/cube3d.h"

void	ft_lstwrite(t_map *lst)
{
	if (!lst)
		return ;
	while (lst->next)
	{
		printf("%s\n", lst->line);
		lst = lst->next;
	}
}

int main(int args, char **argv)
{
  t_mlx	mlx;
  int fd;
  char *buffer;
  int check_file;

  check_file = 0;
  ft_bzero(&mlx.args, sizeof(mlx.args));
  fd = open(argv[1], O_RDWR);

  while ((check_file = get_next_line(fd, &buffer)) > 0)
	{
      if (check_arguments(&mlx, buffer) != SUCCESS)
        return (ERROR_ARGUMENTS);
      free(buffer);
  }
  if (check_arguments(&mlx, buffer) != SUCCESS)
      return (ERROR_ARGUMENTS);
  ft_lstwrite(mlx.args.map);
  if (buffer)
    free(buffer);
  // if (check_file == -1)
  //   return (ERROR);
  
  

  if (args == 2)
  {
    parcer_map(argv[1], &mlx.pos);
    // init_map(&mlx.pos);
    init_position(&mlx.pos);
    mlx.mlx_ptr = mlx_init();
    mlx.win = mlx_new_window(mlx.mlx_ptr, mlx.args.screen_w, mlx.args.screen_h, "Game cube3d school_21");
    draw_ray_casting(&mlx);
    mlx_hook(mlx.win, 2, 1L<<0, press_key, &mlx);
    mlx_put_image_to_window(mlx.mlx_ptr, mlx.win, mlx.img.img_ptr, 0, 0);
    mlx_loop(mlx.mlx_ptr);
  }
  else if (args == 3 && !ft_strncmp(argv[2], "--save", 7))
    ft_putstr_fd("\033[31mNO ARGUMENTS TO LOAD MAP.\033[0m\n", 1);
  else
    ft_putstr_fd("\033[31mNO ARGUMENTS TO LOAD MAP.\033[0m\n", 1);

  return (0);
}