/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 05:09:10 by sumjo             #+#    #+#             */
/*   Updated: 2024/02/11 05:32:59 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void draw_map(t_var *var, t_data *image, t_vec *vec)
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
		if (var->map->map[mapX][mapY] > 0)
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
	  if (var->map->map[mapX][mapY] == 1)
	  		color = 0x00FF0000;
	  else if (var->map->map[mapX][mapY] == 2)
	  		color = 0x0000FF00;
	  else if (var->map->map[mapX][mapY] == 3)
	  		color = 0x000000FF;
	  else if (var->map->map[mapX][mapY] == 4)
	  		color = 0x00FFFF00;
	  else if (var->map->map[mapX][mapY] == 5)
	  		color = 0x00FF00FF;

		if(side == 1)
			color = color / 3;

		drawStart += var->vec->up;
		drawEnd += var->vec->up;

		for(int y = drawStart; y < drawEnd; y++)
			my_mlx_pixel_put(image, x, y, color);
	}
}

int main()
{
	t_data image;
	t_vec vec;
	t_key key;
	t_frame frame;
	t_var var;
	t_map map;

	init_mlx(&image);
	init_vec(&vec);
	init_key(&key);
	init_frame(&frame);
	init_map(&map);

	var.image = &image;
	var.vec = &vec;
	var.key = &key;
	var.frame = &frame;
	var.map = &map;

	mlx_hook(image.win_ptr, 2, 0, key_press, &var);
	mlx_hook(image.win_ptr, 3, 1L << 1, key_lift, &var);

	mlx_loop_hook(image.mlx, render, &var);
	mlx_loop(image.mlx);
	return (0);
}

