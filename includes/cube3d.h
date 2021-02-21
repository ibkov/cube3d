#ifndef MINIRT_H
# define MINIRT_H

# include <math.h>
# include "../minilibx_mms_20200219/mlx.h"
# include "../libft/libft.h"

# define WIN_WIDTH 800
# define WIN_HEIGHT 600

#define mapWidth 24
#define mapHeight 24

typedef struct	s_img
{
	void		*img_ptr;
	int			*data; 
	int			size_l;
	int			bpp;
	int			endian;
}				t_img;

typedef struct	p_gmr
{
	double 		posX;
	double 		posY;
	double		dirX;
	double      dirY;
	double		planeX;
	double		planeY;
	int 		worldMap[mapWidth][mapHeight];

	
}				pos_gamer;

typedef struct	s_mlx
{
	void		*mlx_ptr;
	void		*win;
	t_img		img;
	pos_gamer	pos;
}				t_mlx;


int press_key(int keycode, t_mlx *mlx);
int draw_ray_casting(t_mlx *mlx);

#endif
