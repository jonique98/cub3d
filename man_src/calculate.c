/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 03:18:08 by sumjo             #+#    #+#             */
/*   Updated: 2024/02/16 03:48:16 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	calculate_side_dist(t_var *var)
{
	if (var->ray->rayDir.x < 0)
	{
		var->ray->step.x = -1;
		var->ray->sideDist.x = \
		(var->vec->pos.x - var->ray->map.x) * var->ray->deltaDist.x;
	}
	else
	{
		var->ray->step.x = 1;
		var->ray->sideDist.x = \
		(var->ray->map.x + 1.0 - var->vec->pos.x) * var->ray->deltaDist.x;
	}
	if (var->ray->rayDir.y < 0)
	{
		var->ray->step.y = -1;
		var->ray->sideDist.y = \
		(var->vec->pos.y - var->ray->map.y) * var->ray->deltaDist.y;
	}
	else
	{
		var->ray->step.y = 1;
		var->ray->sideDist.y = \
		(var->ray->map.y + 1.0 - var->vec->pos.y) * var->ray->deltaDist.y;
	}
}

void calculate_ray_values(t_var *var, int x)
{
	var->ray->cameraX = 2 * x / (double)screenWidth - 1;
	var->ray->rayDir.x = var->vec->dir.x + \
	var->vec->plane.x * var->ray->cameraX;
	var->ray->rayDir.y = var->vec->dir.y + \
	var->vec->plane.y * var->ray->cameraX;
	var->ray->map.x = (int)var->vec->pos.x;
	var->ray->map.y = (int)var->vec->pos.y;
	var->ray->deltaDist.x = fabs(1 / var->ray->rayDir.x);
	var->ray->deltaDist.y = fabs(1 / var->ray->rayDir.y);
	var->ray->hit = 0;
}

void	calculate_wall_hit_dda(t_var *var)
{
	while (var->ray->hit == 0)
	{
		if (var->ray->sideDist.x < var->ray->sideDist.y)
		{
			var->ray->sideDist.x += var->ray->deltaDist.x;
			var->ray->map.x += var->ray->step.x;
			var->ray->side = 0;
		}
		else
		{
			var->ray->sideDist.y += var->ray->deltaDist.y;
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
		var->ray->perpWallDist.x = \
		(var->ray->map.x - var->vec->pos.x + \
		(1 - var->ray->step.x) / 2) / var->ray->rayDir.x;
	else
		var->ray->perpWallDist.x = \
		(var->ray->map.y - var->vec->pos.y + \
		(1 - var->ray->step.y) / 2) / var->ray->rayDir.y;
}

void	calculate_draw_start_end(t_var *var)
{
	var->ray->lineHeight = (int)(screenHeight / var->ray->perpWallDist.x);
	var->ray->drawStart = -var->ray->lineHeight / 2 + screenHeight / 2;
	if (var->ray->drawStart < 0)
		var->ray->drawStart = 0;
	var->ray->drawEnd = var->ray->lineHeight / 2 + screenHeight / 2;
	if (var->ray->drawEnd >= screenHeight)
		var->ray->drawEnd = screenHeight - 1;
}
