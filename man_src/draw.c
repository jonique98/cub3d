/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiko <jiko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 05:11:15 by sumjo             #+#    #+#             */
/*   Updated: 2024/02/28 22:33:21 by jiko             ###   ########.fr       */
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

void	draw_background(int line, t_var *var)
{
	int	x;
	int	y;

	x = 0;
	while (x < var->image->width)
	{
		y = 0;
		while (y < var->image->height)
		{
			if (y < line)
				my_mlx_pixel_put(var->image, x, y, var->map->ceiling);
			else
				my_mlx_pixel_put(var->image, x, y, var->map->floor);
			y++;
		}
		x++;
	}
}

void	draw_minimap(t_var *var)
{
	int	tmp_x;
	int	tmp_y;
	int	i;
	int	j;

	i = -11;
	while (++i <= 10)
	{
		j = -11;
		while (++j <= 10)
		{
			tmp_x = var->vec->pos.x + i;
			tmp_y = var->vec->pos.y + j;
			if (is_inside_map(tmp_x, tmp_y, var->map))
			{
				if (var->map->map[tmp_y][tmp_x] != 0)
					draw_sq(var->image, (i + 10) * 10, (j + 10) * 10, 0x000000);
				else
					draw_sq(var->image, (i + 10) * 10, (j + 10) * 10, 0xFFFFFF);
			}
			else
				draw_sq(var->image, (i + 10) * 10, (j + 10) * 10, 0x000000);
		}
	}
	draw_sq(var->image, 10 * 10, 10 * 10, 0xFF0000);
}

void	draw(t_var *var)
{
	make_new_img(var->image);
	draw_background(var->image->height / 2, var);
	draw_map(var);
	draw_minimap(var);
	mlx_put_image_to_window
		(var->image->mlx, var->image->win_ptr, var->image->img, 0, 0);
}
