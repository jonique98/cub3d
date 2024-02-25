/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiko <jiko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 00:29:58 by jiko              #+#    #+#             */
/*   Updated: 2024/02/26 01:03:21 by jiko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void draw_square(t_data *img, int x, int y, int size, int color)
{
	int i;
	int j;
	
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			my_mlx_pixel_put(img, x + i, y + j, color);
			j++;
		}
		i++;
	}
}
