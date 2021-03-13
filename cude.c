
# include "includes/cube3d.h"
# include <math.h>
# include <stdio.h> 
# include <unistd.h>


int main(int args, char **argv)
{
  t_mlx	mlx;
  // int cheak_safe;

  if (args == 2)
  {
    void    *mlx1;
    void    *img1;
    char    *relative_path = "./test.png";
    int     img_width;
    int     img_height;

    mlx1 = mlx_init();
    img1 = mlx_xpm_file_to_image(mlx, relative_path, &img_width, &img_height);
    printf("%s", img1);

    parcer_map(argv[1], &mlx.pos);
    // init_map(&mlx.pos);
    init_position(&mlx.pos);
    mlx.mlx_ptr = mlx_init();
    mlx.win = mlx_new_window(mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "Game cube3d school_21");
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