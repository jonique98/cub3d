/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josumin <josumin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 03:18:08 by sumjo             #+#    #+#             */
/*   Updated: 2024/02/27 18:46:42 by josumin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	calculate_side_dist(t_var *var)
{
	if (var->ray->ray_dir.x < 0)
	{
		var->ray->step.x = -1;
		var->ray->side_dist.x = \
		(var->vec->pos.x - var->ray->map.x) * var->ray->delta_dist.x;
	}
	else
	{
		var->ray->step.x = 1;
		var->ray->side_dist.x = \
		(var->ray->map.x + 1.0 - var->vec->pos.x) * var->ray->delta_dist.x;
	}
	if (var->ray->ray_dir.y < 0)
	{
		var->ray->step.y = -1;
		var->ray->side_dist.y = \
		(var->vec->pos.y - var->ray->map.y) * var->ray->delta_dist.y;
	}
	else
	{
		var->ray->step.y = 1;
		var->ray->side_dist.y = \
		(var->ray->map.y + 1.0 - var->vec->pos.y) * var->ray->delta_dist.y;
	}
}

void	calculate_ray_values(t_var *var, int x)
{
	var->ray->camera_x = 2 * x / (double)SCREENWIDTH - 1;
	var->ray->ray_dir.x = var->vec->dir.x + \
	var->vec->plane.x * var->ray->camera_x;
	var->ray->ray_dir.y = var->vec->dir.y + \
	var->vec->plane.y * var->ray->camera_x;
	var->ray->map.x = (int)var->vec->pos.x;
	var->ray->map.y = (int)var->vec->pos.y;
	var->ray->delta_dist.x = fabs(1 / var->ray->ray_dir.x);
	var->ray->delta_dist.y = fabs(1 / var->ray->ray_dir.y);
	var->ray->hit = 0;
}

void	calculate_wall_hit_dda(t_var *var)
{
	while (var->ray->hit == 0)
	{
		if (var->ray->side_dist.x < var->ray->side_dist.y)
		{
			var->ray->side_dist.x += var->ray->delta_dist.x;
			var->ray->map.x += var->ray->step.x;
			var->ray->side = 0;
		}
		else
		{
			var->ray->side_dist.y += var->ray->delta_dist.y;
			var->ray->map.y += var->ray->step.y;
			var->ray->side = 1;
		}
		if (var->map->map[var->ray->map.y][var->ray->map.x] == 1)
			var->ray->hit = 1;
	}
}

void	calculate_distance_between_wall(t_var *var)
{
	if (var->ray->side == 0)
		var->ray->perpwall_dist = \
		(var->ray->map.x - var->vec->pos.x + \
		(1 - var->ray->step.x) / 2) / var->ray->ray_dir.x;
	else
		var->ray->perpwall_dist = \
		(var->ray->map.y - var->vec->pos.y + \
		(1 - var->ray->step.y) / 2) / var->ray->ray_dir.y;
}

void	calculate_draw_start_end(t_var *var)
{
	var->ray->line_height = (int)(SCREENHEIGHT / var->ray->perpwall_dist);
	var->ray->draw_start = -var->ray->line_height / 2 + SCREENHEIGHT / 2;
	if (var->ray->draw_start < 0)
		var->ray->draw_start = 0;
	var->ray->draw_end = var->ray->line_height / 2 + SCREENHEIGHT / 2;
	if (var->ray->draw_end >= SCREENHEIGHT)
		var->ray->draw_end = SCREENHEIGHT - 1;
}
