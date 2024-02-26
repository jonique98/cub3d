/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 05:09:37 by sumjo             #+#    #+#             */
/*   Updated: 2024/02/27 06:24:35 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	init_vec_set(t_vec_set *vec, t_map *map)
{
	ft_memset(vec, 0, sizeof(t_vec_set));
	vec->pos.x = map->player_x + 0.02;
	vec->pos.y = map->player_y + 0.02;
	if (map->player_dir == 'N')
	{
		vec->dir.x = -1;
		vec->plane.y = 0.66;
	}
	else if (map->player_dir == 'S')
	{
		vec->dir.x = 1;
		vec->plane.y = -0.66;
	}
	else if (map->player_dir == 'W')
	{
		vec->dir.y = -1;
		vec->plane.x = -0.66;
	}
	else if (map->player_dir == 'E')
	{
		vec->dir.y = 1;
		vec->plane.x = 0.66;
	}
}

void	init_frame(t_frame *frame)
{
	ft_memset(frame, 0, sizeof(t_frame));
	frame->oldTime = get_time();
	frame->moveSpeed = 0.1;
	frame->rotSpeed = 0.07;
}

void	init_mlx(t_data *image)
{
	image->mlx = mlx_init();
	image->win_ptr = \
		mlx_new_window(image->mlx, screenWidth, screenHeight, "Hellow World!");
	image->img = \
		mlx_new_image(image->mlx, screenWidth, screenHeight);
	image->addr = mlx_get_data_addr
		(image->img, &image->bits_pixel, &image->line_length, &image->endian);
	image->addr_tex = (int *)mlx_get_data_addr
		(image->img, &image->bits_pixel, &image->line_length, &image->endian);
	image->width = screenWidth;
	image->height = screenHeight;
}
