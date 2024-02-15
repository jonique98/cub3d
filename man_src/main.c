/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 05:09:10 by sumjo             #+#    #+#             */
/*   Updated: 2024/02/16 04:54:03 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

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
		draw_wall(var, x, color);
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

