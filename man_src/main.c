/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 05:09:10 by sumjo             #+#    #+#             */
/*   Updated: 2024/02/27 06:26:09 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	calculate_direction(t_var *var)
{
	if (var->ray->side == 0 && var->ray->rayDir.x < 0)
		var->tex_var.direction = 0;
	else if (var->ray->side == 0 && var->ray->rayDir.x > 0)
		var->tex_var.direction = 1;
	else if (var->ray->side == 1 && var->ray->rayDir.y < 0)
		var->tex_var.direction = 2;
	else
		var->tex_var.direction = 3;
}

void	draw_texture(t_var *var, int x)
{
	int		texY;
	int		color;
	int		y;

	y = var->ray->drawStart;
	var->tex_var.step = 1.0 * var->tex->height / var->ray->lineHeight;
	var->tex_var.texPos = (var->ray->drawStart - screenHeight \
	/ 2 + var->ray->lineHeight / 2) * var->tex_var.step;
	while (y < var->ray->drawEnd)
	{
		texY = (int)var->tex_var.texPos & (var->tex->height - 1);
		var->tex_var.texPos += var->tex_var.step;
		color = var->tex[var->tex_var.direction] \
		.texture[var->tex->height * texY + var->tex_var.texX];
		if (var->ray->side == 1)
			color = (color >> 1) & 8355711;
		my_mlx_pixel_put(var->image, x, y, color);
		y++;
	}
}

void	draw_map(t_var *var)
{
	int		x;
	double	w;

	x = 0;
	w = screenWidth;
	while (x < w)
	{
		calculate_ray_values(var, x);
		calculate_side_dist(var);
		calculate_wall_hit_dda(var);
		calculate_distance_between_wall(var);
		calculate_draw_start_end(var);
		texture_mapping(var);
		calculate_direction(var);
		draw_texture(var, x);
		x++;
	}
}

int mouse_event_draw(int x, int y, t_var *var)
{
	var->key->mouse_x = x;
	var->key->mouse_y = y;
	return (0);
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

	init_map(argc, argv, &map);
	var.map = &map;

	init_mlx(&image);
	var.image = &image;

	init_texture(&image, &var);
	init_vec_set(&vec, &map);
	ft_memset(&ray, 0, sizeof(t_ray));
	ft_memset(&key, 0, sizeof(t_key));
	key.mouse_x = screenWidth / 2;
	key.mouse_y = screenHeight / 2;
	init_frame(&frame);

	var.vec = &vec;
	var.key = &key;
	var.frame = &frame;
	var.ray = &ray;

	mlx_hook(image.win_ptr, 2, 0, key_press, &var);
	mlx_hook(image.win_ptr, 3, 1L << 1, key_lift, &var);
	// mlx_hook(image.win_ptr, 6, 0, mouse_event_draw, &var);

	mlx_loop_hook(image.mlx, render, &var);
	mlx_loop(image.mlx);
	exit (0);
}

