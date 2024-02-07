#include<stdio.h>
#include <mlx.h>
#include <math.h>

#define mapWidth 24
#define mapHeight 24
#define screenWidth 640
#define screenHeight 480

int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
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

typedef struct s_data
{
	void *img;
	char *addr;
	int bits_pixel;
	int line_length;
	int endian;
} t_data;

typedef struct s_pos
{
	double x;
	double y;
} t_pos;

typedef struct s_dir
{
	double x;
	double y;
} t_dir;

typedef struct s_plane
{
	double x;
	double y;
} t_plane;


typedef struct s_vec
{
	t_pos pos;
	t_dir dir;
	t_plane plane;
} t_vec;


void			my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_pixel / 8));
	*(unsigned int*)dst = color;
}

void init_vec(t_vec *vec)
{
	vec->pos.x = 22;
	vec->pos.y = 12;

	vec->dir.x = -1;
	vec->dir.y = 0;

	vec->plane.x = 0;
	vec->plane.y = 0.66;
}

int main()
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_data image;
	t_vec vec;

	init_vec(&vec);

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 500, 500, "Hellow World!");
	image.img = mlx_new_image(mlx_ptr, 500, 500); // 이미지 객체 생성
	image.addr = mlx_get_data_addr(image.img, &image.bits_pixel, &image.line_length, &image.endian);

	double w = screenWidth;
 for(int x = 0; x < w; x++)
    {
      double cameraX = 2 * x / w -1;
      double rayDirX = vec.dir.x + vec.plane.x * cameraX;
      double rayDirY = vec.dir.y + vec.plane.y * cameraX;

	
	  int mapX = (int)vec.pos.x;
	  int mapY = (int)vec.pos.y;

	  double sideDistX;
	  double sideDistY;

	  double deltaDistX = fabs(1 / rayDirX);
	  double deltaDistY = fabs(1 / rayDirY);

	  double perpWallDist = 0;
	  perpWallDist  = 0;

	  int stepX;
	  int stepY;

	  int hit = 0;
	  int side;

	  if (rayDirX < 0)
	  {
		  stepX = -1;
		  sideDistX = (vec.pos.x - mapX) * deltaDistX;
	  }
	  else
	  {
		  stepX = 1;
		  sideDistX = (mapX + 1.0 - vec.pos.x) * deltaDistX;
	  }
	  if (rayDirY < 0)
	  {
		  stepY = -1;
		  sideDistY = (vec.pos.y - mapY) * deltaDistY;
	  }
	  else
	  {
		  stepY = 1;
		  sideDistY = (mapY + 1.0 - vec.pos.y) * deltaDistY;
	  }

		while (hit == 0)
      {
        //jump to next map square, OR in x-direction, OR in y-direction
        if (sideDistX < sideDistY)
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
        if (worldMap[mapX][mapY] > 0)
			hit = 1;
      } 

	}



	// for(int i = 0; i < 500; i++)
	// 	my_mlx_pixel_put(&image, i, i, 0x00FFFFFF);


	// mlx_put_image_to_window(mlx_ptr, win_ptr, image.img, 0, 0);
	// mlx_loop(mlx_ptr); // loop를 돌면서 event를 기다리고, 생성한 윈도우를 Rendering한다. 
	return (0);
}
