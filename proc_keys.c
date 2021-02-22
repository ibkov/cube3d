#include "includes/cube3d.h"

int press_key(int keycode, t_mlx *mlx)
{
    if (keycode == 126)
    {
      mlx->img.img_ptr = mlx_new_image(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
      if(mlx->pos.worldMap[(int)(mlx->pos.posX + mlx->pos.dirX)][(int)(mlx->pos.posY)] == 0) mlx->pos.posX += mlx->pos.dirX;
      if(mlx->pos.worldMap[(int)(mlx->pos.posX)][(int)(mlx->pos.posY + mlx->pos.dirY)] == 0) mlx->pos.posY += mlx->pos.dirY;
      draw_ray_casting(mlx);
      mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, mlx->img.img_ptr, 0, 0);
    }
    if (keycode == 125)
    {
      mlx_clear_window(mlx->mlx_ptr, mlx->win);
      if(mlx->pos.worldMap[(int)(mlx->pos.posX - mlx->pos.dirX)][(int)(mlx->pos.posY)] == 0) mlx->pos.posX -= mlx->pos.dirX;
      if(mlx->pos.worldMap[(int)(mlx->pos.posX)][(int)(mlx->pos.posY - mlx->pos.dirY)] == 0) mlx->pos.posY -= mlx->pos.dirY;
      draw_ray_casting(mlx);
      mlx_clear_window(mlx->mlx_ptr, mlx->win);
      mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, mlx->img.img_ptr, 0, 0);
    }
    if (keycode == 123)
    {
      double rotSpeed = 0.5;
      mlx_clear_window(mlx->mlx_ptr, mlx->win);
      double oldDirX = mlx->pos.dirX;
      mlx->pos.dirX = mlx->pos.dirX * cos(rotSpeed) - mlx->pos.dirY * sin(rotSpeed);
      mlx->pos.dirY = oldDirX * sin(rotSpeed) + mlx->pos.dirY * cos(rotSpeed);
      double oldPlaneX = mlx->pos.planeX;
      mlx->pos.planeX = mlx->pos.planeX * cos(rotSpeed) - mlx->pos.planeY * sin(rotSpeed);
      mlx->pos.planeY = oldPlaneX * sin(rotSpeed) + mlx->pos.planeY * cos(rotSpeed);
      draw_ray_casting(mlx);
      mlx_clear_window(mlx->mlx_ptr, mlx->win);
      mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, mlx->img.img_ptr, 0, 0);
    }
    if (keycode == 124)
    {
      double rotSpeed = 0.5;
      mlx_clear_window(mlx->mlx_ptr, mlx->win);
      double oldDirX = mlx->pos.dirX;
      mlx->pos.dirX = mlx->pos.dirX * cos(-rotSpeed) - mlx->pos.dirY * sin(-rotSpeed);
      mlx->pos.dirY = oldDirX * sin(-rotSpeed) + mlx->pos.dirY * cos(-rotSpeed);
      double oldPlaneX = mlx->pos.planeX;
      mlx->pos.planeX = mlx->pos.planeX * cos(-rotSpeed) - mlx->pos.planeY * sin(-rotSpeed);
      mlx->pos.planeY = oldPlaneX * sin(-rotSpeed) + mlx->pos.planeY * cos(-rotSpeed);
      draw_ray_casting(mlx);
      mlx_clear_window(mlx->mlx_ptr, mlx->win);
      mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, mlx->img.img_ptr, 0, 0);
    }
    return(0);
}