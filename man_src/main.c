/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 05:09:10 by sumjo             #+#    #+#             */
/*   Updated: 2024/02/28 21:47:25 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	calculate_direction(t_var *var)
{
	if (var->ray->side == 0 && var->ray->ray_dir.x < 0)
		var->tex_var.direction = 2;
	else if (var->ray->side == 0 && var->ray->ray_dir.x >= 0)
		var->tex_var.direction = 3;
	else if (var->ray->side == 1 && var->ray->ray_dir.y < 0)
		var->tex_var.direction = 0;
	else
		var->tex_var.direction = 1;
}

void	draw_texture(t_var *var, int x)
{
	int		tex_y;
	int		color;
	int		y;

	y = var->ray->draw_start;
	var->tex_var.step = 1.0 * var->tex->height / var->ray->line_height;
	var->tex_var.tex_pos = (var->ray->draw_start - SCREENHEIGHT \
	/ 2 + var->ray->line_height / 2) * var->tex_var.step;
	while (y < var->ray->draw_end)
	{
		tex_y = (int)var->tex_var.tex_pos & (var->tex->height - 1);
		var->tex_var.tex_pos += var->tex_var.step;
		color = var->tex[var->tex_var.direction] \
		.texture[var->tex->height * tex_y + var->tex_var.tex_x];
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
	w = SCREENWIDTH;
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

int	end(void)
{
	exit(0);
}

int	main(int argc, char **argv)
{
	t_var	var;
	t_map	map;

	init_map(argc, argv, &map);
	var.map = &map;
	init1(&var);
	init2(&var);
	mlx_hook(var.image->win_ptr, 2, 0, key_press, &var);
	mlx_hook(var.image->win_ptr, 3, 1L << 1, key_lift, &var);
	mlx_hook(var.image->win_ptr, 6, 0, mouse_event_draw, &var);
	mlx_hook(var.image->win_ptr, 17, 0, end, &var);
	mlx_loop_hook(var.image->mlx, render, &var);
	mlx_loop(var.image->mlx);
	exit (0);
}
