/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiko <jiko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 05:09:37 by sumjo             #+#    #+#             */
/*   Updated: 2024/02/28 20:22:56 by jiko             ###   ########.fr       */
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

void	init1(t_var *var)
{
	t_data		*image;
	t_vec_set	*vec;
	t_frame		*frame;

	image = ft_calloc(1, sizeof(t_data));
	vec = ft_calloc(1, sizeof(t_vec_set));
	frame = ft_calloc(1, sizeof(t_frame));
	init_mlx(image);
	var->image = image;
	init_texture(image, var);
	init_vec_set(vec, var->map);
	init_frame(frame);
	var->vec = vec;
	var->frame = frame;
}

void	init2(t_var *var)
{
	t_key		*key;
	t_ray		*ray;

	key = ft_calloc(1, sizeof(t_key));
	ray = ft_calloc(1, sizeof(t_ray));
	key->mouse_x = SCREENWIDTH / 2;
	key->mouse_y = SCREENHEIGHT / 2;
	var->key = key;
	var->ray = ray;
}

void	init_frame(t_frame *frame)
{
	ft_memset(frame, 0, sizeof(t_frame));
	frame->move_speed = 0.1;
	frame->rot_speed = 0.07;
}

void	init_mlx(t_data *image)
{
	image->mlx = mlx_init();
	image->win_ptr = \
		mlx_new_window(image->mlx, SCREENWIDTH, SCREENHEIGHT, "Hellow World!");
	image->img = \
		mlx_new_image(image->mlx, SCREENWIDTH, SCREENHEIGHT);
	image->addr = mlx_get_data_addr
		(image->img, &image->bits_pixel, &image->line_length, &image->endian);
	image->addr_tex = (int *)mlx_get_data_addr
		(image->img, &image->bits_pixel, &image->line_length, &image->endian);
	image->width = SCREENWIDTH;
	image->height = SCREENHEIGHT;
}
