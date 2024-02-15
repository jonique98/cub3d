/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 05:09:10 by sumjo             #+#    #+#             */
/*   Updated: 2024/02/16 07:42:32 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int *texture_copy(t_data *img)
{
	t_data img2;
	int *result;

	int row = 0;
	int col = 0;

	img2.mlx = img->mlx;
	img2.img = mlx_xpm_file_to_image(img2.mlx, "/Users/sumjo/Desktop/cub/sample_640×426.xpm", &img2.width, &img2.height);
	img2.addr_tex = (int *)mlx_get_data_addr(img2.img, &img2.bits_pixel, &img2.line_length, &img2.endian);
	result = (int *)malloc(sizeof(int) * img2.width * img2.height);

	row = -1;
	while (++row < img2.height)
	{
		col = -1;
		while (++col < img2.width)
		{
			result[img2.width * row + col] = img2.addr_tex[img2.width * row + col];
		}
	}
	mlx_destroy_image(img->mlx, img2.img);
	return (result);
}

void init_width_height(t_data *img, t_texture *texture)
{
	t_data img2;
	img2.img = mlx_xpm_file_to_image(img->mlx, "./teapot.xpm", &img2.width, &img2.height);
	texture->width = img2.width;
	texture->height = img2.height;
	mlx_destroy_image(img->mlx, img2.img);
}

void draw_wall(t_var *var, int x, int color)
{
	int y;

	y = var->ray->drawStart;
	while (y < var->ray->drawEnd)
	{
		my_mlx_pixel_put(var->image, x, y, color);
		y++;
	}
}

void	draw_map(t_var *var)
{
	int		x;
	double	w;
	int		color;

	x = 0;
	w = screenWidth;
	while (x < w)
	{
		calculate_ray_values(var, x);
		calculate_side_dist(var);
		calculate_wall_hit_dda(var);
		calculate_distance_between_wall(var);
		if (var->ray->side == 1)
			color = 0x00fff;
		else
			color = 0x000000;
		calculate_draw_start_end(var);
	double wallX;
	if (var->ray->side == 0)
		wallX = var->vec->pos.y + var->ray->perpWallDist * var->ray->rayDir.y;
	else
		wallX = var->vec->pos.x + var->ray->perpWallDist * var->ray->rayDir.x;
	wallX -= floor((wallX));
	
	int texX = (int)(wallX * (double)var->texture[0].width);
	if (var->ray->side == 0 && var->ray->rayDir.x > 0)
		texX = var->texture[0].width - texX - 1;
	if (var->ray->side == 1 && var->ray->rayDir.y < 0)
		texX = var->texture[0].width - texX - 1;

	double step = 1.0 * var->texture[0].height / var->ray->lineHeight;
	double texPos = (var->ray->drawStart - screenHeight / 2 + var->ray->lineHeight / 2) * step;

	int y = var->ray->drawStart;
	while (y < var->ray->drawEnd)
	{
		int texY = (int)texPos & ((int)var->texture[0].height - 1);
		texPos += step;
		int color = var->texture[0].texture[(int)var->texture[0].width * texY + texX];
		my_mlx_pixel_put(var->image, x, y, color);
		y++;
	}
	x++;
	}
}

void init_texture(t_texture *texture, t_map *map)
{
	texture->tex_path = map->no;
	texture->texture = (int *)malloc(sizeof(int) * 64 * 64);
	texture->width = 64;
	texture->height = 64;
}

int main(int argc, char **argv)
{
	t_data image;
	t_vec_set vec;
	t_key key;
	t_frame frame;
	t_var var;
	t_map map;
	t_ray ray;
	t_texture texture;


	init_map(argc, argv, &map);
	init_mlx(&image);

	init_width_height(&image, &texture);
	texture.texture = texture_copy(&image);
	var.texture[0] = texture;

	init_vec_set(&vec, &map);
	init_ray(&ray);
	init_key(&key);
	init_frame(&frame);
	init_texture(&texture, &map);

	var.image = &image;
	var.vec = &vec;
	var.key = &key;
	var.frame = &frame;
	var.map = &map;
	var.ray = &ray;

	mlx_hook(image.win_ptr, 2, 0, key_press, &var);
	mlx_hook(image.win_ptr, 3, 1L << 1, key_lift, &var);

	mlx_loop_hook(image.mlx, render, &var);
	mlx_loop(image.mlx);
	return (0);
}

