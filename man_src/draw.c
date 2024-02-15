/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 05:11:15 by sumjo             #+#    #+#             */
/*   Updated: 2024/02/16 06:46:04 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= screenWidth || y < 0 || y >= screenHeight)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_pixel / 8));
	*(unsigned int *)dst = color;
}

void	make_new_img(t_data *image)
{
	mlx_destroy_image(image->mlx, image->img);
	image->img = mlx_new_image(image->mlx, screenHeight, screenWidth);
	image->addr = mlx_get_data_addr(image->img, \
	&image->bits_pixel, &image->line_length, &image->endian);
}

void	draw_background(int line, t_data *image)
{
	int	x;
	int	y;

	x = 0;
	while (x < image->width)
	{
		y = 0;
		while (y < image->height)
		{
			if (y < line)
				my_mlx_pixel_put(image, x, y, 0x87CEEB);
			else
				my_mlx_pixel_put(image, x, y, 0x228B22);
			y++;
		}
		x++;
	}
}

void	draw(t_var *var)
{
	make_new_img(var->image);
	draw_background(var->image->height / 2, var->image);
	draw_map(var);
	// var->frame->time = get_time();
	// var->frame->frameTime = \
		// (var->frame->time - var->frame->oldTime) / 1000000.0;
	mlx_put_image_to_window
		(var->image->mlx, var->image->win_ptr, var->image->img, 0, 0);
	// var->frame->oldTime = var->frame->time;
	// var->frame->moveSpeed = var->frame->frameTime * 5.0;
	// var->frame->rotSpeed = var->frame->frameTime * 3.0;
}
