
# include "includes/cube3d.h"
# include <math.h>
# include <stdio.h> 



void verLine(int x, int drawStart, int drawEnd, int color, t_mlx mlx)
{
    while (drawStart < drawEnd)
    {
        mlx.img.data[drawStart * WIN_WIDTH + x] = color;
        drawStart++;
    }
}

int draw_ray_casting(t_mlx *mlx)
{
      //One more time with mlx_new_image
      mlx->img.img_ptr = mlx_new_image(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);

      mlx->img.data = (int *)mlx_get_data_addr(mlx->img.img_ptr, &mlx->img.bpp, &mlx->img.size_l,
		  &mlx->img.endian);
      
  for(int x = 0; x < WIN_WIDTH; x++)
    {
      //calculate ray position and direction
      double cameraX = 2 * x / (double)WIN_WIDTH - 1; //x-coordinate in camera space
      double rayDirX = mlx->pos.dirX + mlx->pos.planeX * cameraX;
      double rayDirY = mlx->pos.dirY + mlx->pos.planeY * cameraX;
      //which box of the map we're in
      int mapX = (int)(mlx->pos.posX);
      int mapY = (int)(mlx->pos.posY);

      //length of ray from current position to next x or y-side
      double sideDistX;
      double sideDistY;

       //length of ray from one x or y-side to next x or y-side
      double deltaDistX = fabs(1 / rayDirX);
      double deltaDistY = fabs(1 / rayDirY);
      double perpWallDist;

      //what direction to step in x or y-direction (either +1 or -1)
      int stepX;
      int stepY;

      int hit = 0; //was there a wall hit?
      int side; //was a NS or a EW wall hit?
      //calculate step and initial sideDist

      
      if(rayDirX < 0)
      {
        stepX = -1;
        sideDistX = (mlx->pos.posX - mapX) * deltaDistX;
      }
      else
      {
        stepX = 1;
        sideDistX = (mapX + 1.0 - mlx->pos.posX) * deltaDistX;
      }
      if(rayDirY < 0)
      {
        stepY = -1;
        sideDistY = (mlx->pos.posY - mapY) * deltaDistY;
      }
      else
      {
        stepY = 1;
        sideDistY = (mapY + 1.0 - mlx->pos.posY) * deltaDistY;
      }
      //perform DDA
      while (hit == 0)
      {
        //jump to next map square, OR in x-direction, OR in y-direction
        if(sideDistX < sideDistY)
        {
          sideDistX += deltaDistX;
          mapX += stepX;
          side = 0;
        }
        else
        {
          sideDistY += deltaDistY;
          mapY += stepY;
          side = 1;
        }
        //Check if ray has hit a wall
        if(mlx->pos.worldMap[mapX][mapY] > 0) hit = 1;
      }
      //Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
      if(side == 0) perpWallDist = (mapX - mlx->pos.posX + (1 - stepX) / 2) / rayDirX;
      else          perpWallDist = (mapY - mlx->pos.posY + (1 - stepY) / 2) / rayDirY;

      //Calculate height of line to draw on screen
      int lineHeight = (int)(WIN_HEIGHT / perpWallDist);

      //calculate lowest and highest pixel to fill in current stripe
      int drawStart = -lineHeight / 2 + WIN_HEIGHT / 2;
      if(drawStart < 0)drawStart = 0;
      int drawEnd = lineHeight / 2 + WIN_HEIGHT / 2;
      if(drawEnd >= WIN_HEIGHT)drawEnd = WIN_HEIGHT - 1;

      //choose wall color
      int color = 0xFFFFFF;
      int red_color = 0xff3333;
      int green_color = 0x339933;
      int blue_color = 0x3366cc;
      int yellow_color = 0xffff55;
      if (mlx->pos.worldMap[mapX][mapY] == 1)
        color = red_color;
      if (mlx->pos.worldMap[mapX][mapY] == 2)
        color = green_color;
      if (mlx->pos.worldMap[mapX][mapY] == 3)
        color = blue_color;
      if (mlx->pos.worldMap[mapX][mapY] == 4)
        color = 0xFFFFFF; 
      if (mlx->pos.worldMap[mapX][mapY] == 4)
        color = yellow_color; 

      //give x and y sides different brightness
      if(side == 1) {color = color / 1.5;}
    

      //draw the pixels of the stripe as a vertical line
      verLine(x, drawStart, drawEnd, color, *mlx);
    }
    return (0);
}

void init_position(pos_gamer *pos)
{
  pos->posX = 20;
  pos->posY = 12;  //x and y start position
  pos->dirX = -1;
  pos->dirY = 0; //initial direction vector
  pos->planeX = 0; 
  pos->planeY = 0.66; //the 2d raycaster version of camera plane
}

void init_map(pos_gamer *pos)
{

  int i;
  int j;
  i = 0;
  j = 0;

  while(i <= mapWidth)
  {
    j = 0;
    while(j <= mapHeight)
    {
      pos->worldMap[i][j] = 0;
      j++;
    }
    i++;
  }

  int tempMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};
  
  i = 0;
  while(i <= mapWidth)
  {
    j = 0;
    while(j <= mapHeight)
    {
      pos->worldMap[i][j] = tempMap[i][j];
      write(1, &tempMap[i][j] + 48, 1);
      j++;
    }
    i++;
  }
}

int main()
{
  t_mlx	mlx;
  init_map(&mlx.pos);
  init_position(&mlx.pos);
  mlx.mlx_ptr = mlx_init();
  mlx.win = mlx_new_window(mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "Game cube3d school_21");
  draw_ray_casting(&mlx);
  mlx_hook(mlx.win, 2, 1L<<0, press_key, &mlx);
  mlx_put_image_to_window(mlx.mlx_ptr, mlx.win, mlx.img.img_ptr, 0, 0);
  mlx_loop(mlx.mlx_ptr);

  return (0);
}