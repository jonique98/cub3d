/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 05:09:37 by sumjo             #+#    #+#             */
/*   Updated: 2024/02/11 05:52:20 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	init_vec(t_vec *vec)
{
	vec->up = 0;
	vec->pos.x = 10;
	vec->pos.y = 14;
	vec->dir.x = 0;
	vec->dir.y = 1;
	vec->plane.x = 0.66;
	vec->plane.y = 0;
}

void	init_key(t_key *key)
{
	key->left_rotate = 0;
	key->right_rotate = 0;
	key->left = 0;
	key->right = 0;
	key->forward = 0;
	key->backward = 0;
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
