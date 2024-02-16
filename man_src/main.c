/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josumin <josumin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 05:09:10 by sumjo             #+#    #+#             */
/*   Updated: 2024/02/16 11:55:00 by josumin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void init_texture(t_data *img, t_var *var)
{
	t_data img2;
	img2.img = mlx_xpm_file_to_image(img->mlx, "/Users/josumin/Desktop/cub/colorstone.xpm", &img2.width, &img2.height);
	img2.addr_tex = (int *)mlx_get_data_addr(img2.img, &img2.bits_pixel, &img2.line_length, &img2.endian);
	var->tex->width = img2.width;
	var->tex->height = img2.height;
	var->tex->texture = (int *)ft_calloc(img2.width * img2.height, sizeof(int));
	
	int x = 0;
	int y = 0;
	
	while (y < img2.height)
	{
		x = 0;
		while (x < img2.width)
		{
			var->tex->texture[img2.width * y + x] = img2.addr_tex[img2.width * y + x];
			x++;
		}
		y++;
	}
	mlx_destroy_image(img->mlx, img2.img);
}

// void draw_wall(t_var *var, int x, int color)
// {
// 	int y;

// 	y = var->ray->drawStart;
// 	while (y < var->ray->drawEnd)
// 	{
// 		my_mlx_pixel_put(var->image, x, y, color);
// 		y++;
// 	}
// }

void	draw_map(t_var *var)
{
	int		x;
	double	w;

	x = 0;
	w = screenWidth;
	while (x < w)
	{
		calculate_ray_values(var, x);
		calculate_side_dist(var);
		calculate_wall_hit_dda(var);
		calculate_distance_between_wall(var);
		calculate_draw_start_end(var);
		double wallx;
		if (var->ray->side == 0)
			wallx = var->vec->pos.y + var->ray->perpWallDist * var->ray->rayDir.y;
		else
			wallx = var->vec->pos.x + var->ray->perpWallDist * var->ray->rayDir.x;
		wallx -= floor((wallx));
		
		int texX = (int)(wallx * (double)var->tex->width);
		if (var->ray->side == 0 && var->ray->rayDir.x > 0)
			texX = var->tex->width - texX - 1;
		if (var->ray->side == 1 && var->ray->rayDir.y < 0)
			texX = var->tex->width - texX - 1;
		
		double step = 1.0 * var->tex->height / var->ray->lineHeight;
		
		double texPos = (var->ray->drawStart - screenHeight / 2 + var->ray->lineHeight / 2) * step;
		for(int y = var->ray->drawStart; y < var->ray->drawEnd; y++)
		{
			int texY = (int)texPos & (var->tex->height - 1);
			texPos += step;
			int color = var->tex->texture[var->tex->height * texY + texX];
			if (var->ray->side == 1)
				color = (color >> 1) & 8355711;
			my_mlx_pixel_put(var->image, x, y, color);
		}
	x++;
	}
}

int main(int argc, char **argv)
{
	t_data image;
	t_vec_set vec;
	t_key key;
	t_frame frame;
	t_var var;
	t_map map;
	t_ray ray;
	t_texture texture;
	
	var.tex = &texture;

	var.tex->tex_path = 0;
	var.tex->texture = 0;
	var.tex->width = 0;
	var.tex->height = 0;

	init_map(argc, argv, &map);
	init_mlx(&image);
	init_texture(&image, &var);
	init_vec_set(&vec, &map);
	init_ray(&ray);
	init_key(&key);
	init_frame(&frame);
	
	printf("tex width: %d\n", var.tex->width);
	printf("tex height: %d\n", var.tex->height);

	var.image = &image;
	var.vec = &vec;
	var.key = &key;
	var.frame = &frame;
	var.map = &map;
	var.ray = &ray;
	

	mlx_hook(image.win_ptr, 2, 0, key_press, &var);
	mlx_hook(image.win_ptr, 3, 1L << 1, key_lift, &var);

	mlx_loop_hook(image.mlx, render, &var);
	mlx_loop(image.mlx);
	return (0);
}

