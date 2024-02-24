/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiko <jiko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 05:09:10 by sumjo             #+#    #+#             */
/*   Updated: 2024/02/24 18:35:34 by jiko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void init_texture(t_data *img, t_var *var)
{
	t_data img2;
	img2.img = mlx_xpm_file_to_image(img->mlx, "./AnyConv.com__ins (3).xpm", &img2.width, &img2.height);
	img2.addr_tex = (int *)mlx_get_data_addr(img2.img, &img2.bits_pixel, &img2.line_length, &img2.endian);
	var->tex->width = img2.width;
	var->tex->height = img2.height;
	var->tex->texture = (int *)ft_calloc(texHeight*texWidth, sizeof(int));
	
	for(int i = 0; i < texHeight; i++){
		for(int j = 0; j < texWidth; j++){
			int color;
			int height = var->tex->height;
			int width = var->tex->width;
			int result_row = (height * i) / texHeight;
			int result_col = (width * j) / texWidth;
			
			if (result_row < 0)
				result_row = 0;
			if (result_col < 0)
				result_col = 0;
			color = img2.addr_tex[img2.width * result_row + result_col];
			var->tex->texture[texWidth * i + j] = color;
		}
	}
	var->tex->width = texWidth;
	var->tex->height = texHeight;
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
	
	ft_memset(&texture, 0, sizeof(t_texture));
	var.tex = &texture;

	init_map(argc, argv, &map);
	init_mlx(&image);
	init_texture(&image, &var);
	init_vec_set(&vec, &map);
	ft_memset(&ray, 0, sizeof(t_ray));
	ft_memset(&key, 0, sizeof(t_key));
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
	exit (0);
}

