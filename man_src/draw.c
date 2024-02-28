/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiko <jiko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 05:11:15 by sumjo             #+#    #+#             */
/*   Updated: 2024/02/28 19:59:03 by jiko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= SCREENWIDTH || y < 0 || y >= SCREENHEIGHT)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_pixel / 8));
	*(unsigned int *)dst = color;
}

void	make_new_img(t_data *image)
{
	mlx_destroy_image(image->mlx, image->img);
	image->img = mlx_new_image(image->mlx, SCREENWIDTH, SCREENHEIGHT);
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

void	draw_minimap(t_var *var, int size)
{
	int	tmp_x;
	int	tmp_y;
	int	i;
	int	j;

	i = -size;
	while (i <= size)
	{
		j = -size;
		while (j <= size)
		{
			tmp_x = var->vec->pos.x + i;
			tmp_y = var->vec->pos.y + j;
			if (tmp_x >= 0 && tmp_x < var->map->map_width && tmp_y >= 0 && tmp_y < var->map->map_height)
				if (var->map->map[tmp_y][tmp_x] == 1)
					draw_square(var->image, (i + size) * size, (j + size) * size, size, 0x000000);
				else
					draw_square(var->image, (i + size) * size, (j + size) * size, size, 0xFFFFFF);
			else
				draw_square(var->image, (i + size) * size, (j + size) * size, size, 0x000000);
			j++;
		}
		i++;
	}
	draw_square(var->image, size * size, size * size, size, 0xFF0000);
}

void	draw(t_var *var)
{
	make_new_img(var->image);
	draw_background(var->image->height / 2, var->image);
	draw_map(var);
	draw_minimap(var, 10);
	mlx_put_image_to_window
		(var->image->mlx, var->image->win_ptr, var->image->img, 0, 0);
}
