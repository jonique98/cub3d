#include<stdio.h>
#include <mlx.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

#define mapWidth 24
#define mapHeight 24
#define screenWidth 1000
#define screenHeight 1000

int up = 0;

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

typedef struct s_key
{
	int left_rotate;
	int right_rotate;
	int left;
	int right;
	int forward;
	int backward;
	int up;
	int down;
} t_key;

typedef struct s_data
{
	void *win_ptr;
	void *mlx;
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

typedef struct s_param
{
	t_data *image;
	t_vec *vec;
	t_key *key;
} t_param;


void			my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_pixel / 8));
	*(unsigned int*)dst = color;
}

void init_vec(t_vec *vec)
{
	vec->pos.x = 10;
	vec->pos.y = 14;

	vec->dir.x = 0;
	vec->dir.y = 1;

	vec->plane.x = 0.66;
	vec->plane.y = 0;
}

void draw_background(int line, t_data *image)
{
	line += up;
	for(int x = 0; x < screenWidth; x++)
	{
		for(int y = 0; y < screenHeight; y++)
		{
			if(y < line)
				my_mlx_pixel_put(image, x, y, 0x00B0E0E6);
			else
				my_mlx_pixel_put(image, x, y, 0x00A9A9A9);
		}
	}
}

void draw_map(t_data *image, t_vec *vec)
{
	double w = screenWidth;
	// double w = mapHeight;
 for(int x = 0; x < w; x++)
	{
	  double cameraX = 2 * x / w -1;
	  double rayDirX = vec->dir.x + vec->plane.x * cameraX;
	  double rayDirY = vec->dir.y + vec->plane.y * cameraX;

	  int mapX = (int)vec->pos.x;
	  int mapY = (int)vec->pos.y;

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
		  sideDistX = (vec->pos.x - mapX) * deltaDistX;
	  }
	  else
	  {
		  stepX = 1;
		  sideDistX = (mapX + 1.0 - vec->pos.x) * deltaDistX;
	  }
	  if (rayDirY < 0)
	  {
		  stepY = -1;
		  sideDistY = (vec->pos.y - mapY) * deltaDistY;
	  }
	  else
	  {
		  stepY = 1;
		  sideDistY = (mapY + 1.0 - vec->pos.y) * deltaDistY;
	  }

	  while (hit == 0)
	  {
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

	  if (side == 0)
		perpWallDist = (mapX - vec->pos.x + (1 - stepX) / 2) / rayDirX;
	  else
		perpWallDist = (mapY - vec->pos.y + (1 - stepY) / 2) / rayDirY;

	int h = screenHeight;
	  int lineHeight = (int)(h / perpWallDist);
	  int drawStart = -lineHeight / 2 + h / 2;
	  if(drawStart < 0)drawStart = 0;
	  int drawEnd = lineHeight / 2 + h / 2;
	  if(drawEnd >= h)drawEnd = h - 1;

	  int color = 0x00FFFFFF;
	  if (worldMap[mapX][mapY] == 1)
	  		color = 0x00FF0000;
	  else if (worldMap[mapX][mapY] == 2)
	  		color = 0x0000FF00;
	  else if (worldMap[mapX][mapY] == 3)
	  		color = 0x000000FF;
	  else if (worldMap[mapX][mapY] == 4)
	  		color = 0x00FFFF00;
	  else if (worldMap[mapX][mapY] == 5)
	  		color = 0x00FF00FF;

		if(side == 1)
			color = color / 3;

		drawStart += up;
		drawEnd += up;

		for(int y = drawStart; y < drawEnd; y++)
			my_mlx_pixel_put(image, x, y, color);
	}
}

void	make_new_img(t_data *image)
{
	mlx_destroy_image(image->mlx, image->img);
	image->img = mlx_new_image(image->mlx, screenHeight, screenWidth);
	image->addr = mlx_get_data_addr(image->img, \
	&image->bits_pixel, &image->line_length, &image->endian);
}

void rotate_left(t_vec *vec)
{
	double oldDirX = vec->dir.x;
	vec->dir.x = vec->dir.x * cos(0.1) - vec->dir.y * sin(0.1);
	vec->dir.y = oldDirX * sin(0.1) + vec->dir.y * cos(0.1);
	double oldPlaneX = vec->plane.x;
	vec->plane.x = vec->plane.x * cos(0.1) - vec->plane.y * sin(0.1);
	vec->plane.y = oldPlaneX * sin(0.1) + vec->plane.y * cos(0.1);
}

void rotate_right(t_vec *vec)
{
	double oldDirX = vec->dir.x;
	vec->dir.x = vec->dir.x * cos(-0.1) - vec->dir.y * sin(-0.1);
	vec->dir.y = oldDirX * sin(-0.1) + vec->dir.y * cos(-0.1);
	double oldPlaneX = vec->plane.x;
	vec->plane.x = vec->plane.x * cos(-0.1) - vec->plane.y * sin(-0.1);
	vec->plane.y = oldPlaneX * sin(-0.1) + vec->plane.y * cos(-0.1);
}

void move_left(t_vec *vec)
{
	if (worldMap[(int)(vec->pos.x - vec->dir.y * 0.1)][(int)vec->pos.y] == 0)
		vec->pos.x -= vec->dir.y * 0.1;
	if (worldMap[(int)vec->pos.x][(int)(vec->pos.y + vec->dir.x * 0.1)] == 0)
		vec->pos.y += vec->dir.x * 0.1;
}

void move_right(t_vec *vec)
{
	if (worldMap[(int)(vec->pos.x + vec->dir.y * 0.1)][(int)vec->pos.y] == 0)
		vec->pos.x += vec->dir.y * 0.1;
	if (worldMap[(int)vec->pos.x][(int)(vec->pos.y - vec->dir.x * 0.1)] == 0)
		vec->pos.y -= vec->dir.x * 0.1;
}

void move_forward(t_vec *vec)
{

	if (worldMap[(int)(vec->pos.x + vec->dir.x * 0.1)][(int)vec->pos.y] == 0)
		vec->pos.x += vec->dir.x * 0.1;
	if (worldMap[(int)vec->pos.x][(int)(vec->pos.y + vec->dir.y * 0.1)] == 0)
		vec->pos.y += vec->dir.y * 0.1;
}

void move_backward(t_vec *vec)
{
	if (worldMap[(int)(vec->pos.x - vec->dir.x * 0.1)][(int)vec->pos.y] == 0)
		vec->pos.x -= vec->dir.x * 0.1;
	if (worldMap[(int)vec->pos.x][(int)(vec->pos.y - vec->dir.y * 0.1)] == 0)
		vec->pos.y -= vec->dir.y * 0.1;
}

void draw(t_param *param)
{
	make_new_img(param->image);
	draw_background(screenHeight / 2, param->image);
	draw_map(param->image, param->vec);
	mlx_put_image_to_window(param->image->mlx, param->image->win_ptr, param->image->img, 0, 0);
}

void draw_bullet(t_data *image, int x, int y, float size) {
	int radius = (int)size; // 총알의 크기를 반지름으로 사용

	for (int i = x - radius; i <= x + radius; i++) {
		for (int j = y - radius; j <= y + radius; j++) {
			if ((i - x) * (i - x) + (j - y) * (j - y) <= radius * radius) {
				if (i >= 0 && i < screenWidth && j >= 0 && j < screenHeight) {
					my_mlx_pixel_put(image, i, j, 0xFFFFFF); // 흰색으로 그림
				}
			}
		}
	}
}

int move(int key_code, t_param *param)
{
	if (key_code == 53)
		exit(0);
	else if (key_code == 123)
		param->key->left_rotate = 1;
	else if (key_code == 124)
		param->key->right_rotate = 1;
	else if (key_code == 0)
		param->key->left = 1;
	else if (key_code == 1)
		param->key->backward = 1;
	else if (key_code == 13)
		param->key->forward = 1;
	else if (key_code == 2)
		param->key->right = 1;
	else if (key_code == 125)
		param->key->down = 1;
	else if (key_code == 126)
		param->key->up = 1;
	return (0);
}

int key_lift(int key_code, t_param *param)
{
	if(key_code == 123)
		param->key->left_rotate = 0;
	else if (key_code == 124)
		param->key->right_rotate = 0;
	else if (key_code == 0)
		param->key->left = 0;
	else if (key_code == 1)
		param->key->backward = 0;
	else if (key_code == 13)
		param->key->forward = 0;
	else if (key_code == 2)
		param->key->right = 0;
	else if (key_code == 125)
		param->key->down = 0;
	else if (key_code == 126)
		param->key->up = 0;

	return (0);
}

int		get_delay(int startnow, int min, int mac)
{
	static struct timeval	start;
	static struct timeval	stop;
	unsigned long			delta_us;

	if (startnow)
	{
		gettimeofday(&start, NULL);
		return (0);
	}
	else
		gettimeofday(&stop, NULL);
	delta_us = (stop.tv_sec - start.tv_sec) * 1000000
		+ stop.tv_usec - start.tv_usec;
	if (delta_us < (unsigned long)min)
	{
		if (!mac)
			usleep((min - delta_us) % 1000000);
		return (0);
	}
	return (delta_us - min);
}

int render(t_param *param)
{
	if (param->key->left_rotate)
		rotate_left(param->vec);
	if (param->key->right_rotate)
		rotate_right(param->vec);
	if (param->key->left)
		move_left(param->vec);
	if (param->key->right)
		move_right(param->vec);
	if (param->key->forward)
		move_forward(param->vec);
	if (param->key->backward)
		move_backward(param->vec);
	if (param->key->up)
	{
		if(up < 300)
			up += 20;
	}
	if (param->key->down)
	{
		if(up > -200)
			up -= 20;
	}
	get_delay(1, 16666, 0);
	draw(param);
	// mlx_do_sync(param->image->mlx);
	return (0);
}

void init_key(t_key *key)
{
	key->left_rotate = 0;
	key->right_rotate = 0;
	key->left = 0;
	key->right = 0;
	key->forward = 0;
	key->backward = 0;
}

int main()
{
	t_data image;
	t_vec vec;
	t_key key;
	t_param param;

	init_key(&key);
	init_vec(&vec);

	image.mlx = mlx_init();
	image.win_ptr = mlx_new_window(image.mlx, screenHeight, screenWidth, "Hellow World!");
	image.img = mlx_new_image(image.mlx, screenHeight, screenWidth); // 이미지 객체 생성
	image.addr = mlx_get_data_addr(image.img, &image.bits_pixel, &image.line_length, &image.endian);

	param.image = &image;
	param.vec = &vec;
	param.key = &key;

	draw_background(screenHeight / 2, &image);
	draw_map(&image, &vec);
	mlx_put_image_to_window(image.mlx, image.win_ptr, image.img, 0, 0);

	mlx_hook(image.win_ptr, 2, 0, move, &param);
	mlx_hook(image.win_ptr, 3, 1L << 1, key_lift, &param);

	mlx_loop_hook(image.mlx, render, &param);
	mlx_loop(image.mlx);
	return (0);
}

// void shoot(t_param *param)
// {
// 	double rayDirX = param->vec->dir.x;
// 	double rayDirY = param->vec->dir.y;

// 	int mapX = (int)param->vec->pos.x;
// 	int mapY = (int)param->vec->pos.y;

// 	double sideDistX;
// 	double sideDistY;

// 	double deltaDistX = fabs(1 / rayDirX);
// 	double deltaDistY = fabs(1 / rayDirY);

// 	double perpWallDist = 0;
// 	perpWallDist  = 0;

// 	int stepX;
// 	int stepY;

// 	int hit = 0;
// 	int side;

// 	if (rayDirX < 0)
// 	{
// 		stepX = -1;
// 		sideDistX = (param->vec->pos.x - mapX) * deltaDistX;
// 	}
// 	else
// 	{
// 		stepX = 1;
// 		sideDistX = (mapX + 1.0 - param->vec->pos.x) * deltaDistX;
// 	}

// 	if (rayDirY < 0)
// 	{
// 		stepY = -1;
// 		sideDistY = (param->vec->pos.y - mapY) * deltaDistY;
// 	}
// 	else
// 	{
// 		stepY = 1;
// 		sideDistY = (mapY + 1.0 - param->vec->pos.y) * deltaDistY;
// 	}

// 	while (hit == 0)
// 	{
// 		if (sideDistX < sideDistY)
// 		{
// 			sideDistX += deltaDistX;
// 			mapX += stepX;
// 			side = 0;
// 		}
// 		else
// 		{
// 			sideDistY += deltaDistY;
// 			mapY += stepY;
// 			side = 1;
// 		}
// 		if (worldMap[mapX][mapY] > 0)
// 			hit = 1;
// 	}
// }
