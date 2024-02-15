/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 05:09:37 by sumjo             #+#    #+#             */
/*   Updated: 2024/02/16 03:19:17 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	init_vec_set(t_vec_set *vec, t_map *map)
{
	vec->up = 0;
	vec->pos.x = map->player_x;
	vec->pos.y = map->player_y;
	if (map->player_dir == 'N')
	{
		vec->dir.x = -1;
		vec->dir.y = 0;
		vec->plane.x = 0;
		vec->plane.y = 0.66;
	}
	else if (map->player_dir == 'S')
	{
		vec->dir.x = 1;
		vec->dir.y = 0;
		vec->plane.x = 0;
		vec->plane.y = -0.66;
	}
	else if (map->player_dir == 'W')
	{
		vec->dir.x = 0;
		vec->dir.y = -1;
		vec->plane.x = -0.66;
		vec->plane.y = 0;
	}
	else if (map->player_dir == 'E')
	{
		vec->dir.x = 0;
		vec->dir.y = 1;
		vec->plane.x = 0.66;
		vec->plane.y = 0;
	}
}

void	init_key(t_key *key)
{
	key->left_rotate = 0;
	key->right_rotate = 0;
	key->left = 0;
	key->right = 0;
	key->forward = 0;
	key->backward = 0;
	key->up = 0;
	key->down = 0;
}

void	init_frame(t_frame *frame)
{
	frame->time = 0;
	frame->oldTime = get_time();
	frame->frameTime = 0;
	frame->moveSpeed = 0;
	frame->rotSpeed = 0;
}

void	init_mlx(t_data *image)
{
	image->mlx = mlx_init();
	image->win_ptr = \
		mlx_new_window(image->mlx, screenHeight, screenWidth, "Hellow World!");
	image->img = \
		mlx_new_image(image->mlx, screenHeight, screenWidth);
	image->addr = mlx_get_data_addr
		(image->img, &image->bits_pixel, &image->line_length, &image->endian);
}
void init_ray(t_ray *ray)
{
	ray->cameraX = 0;
	ray->rayDir.x = 0;
	ray->rayDir.y = 0;
	ray->sideDist.x = 0;
	ray->sideDist.y = 0;
	ray->deltaDist.x = 0;
	ray->deltaDist.y = 0;
	ray->perpWallDist.x = 0;
	ray->step.x = 0;
	ray->step.y = 0;
	ray->map.x = 0;
	ray->map.y = 0;
	ray->side = 0;
	ray->lineHeight = 0;
	ray->drawStart = 0;
	ray->drawEnd = 0;
	ray->hit = 0;
	ray->side = 0;
}
