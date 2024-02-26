/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 05:09:10 by sumjo             #+#    #+#             */
/*   Updated: 2024/02/27 01:22:53 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"


void	copy_texture(t_data *img, t_var *var, int idx)
{
	int	i;
	int	j;
	int	color;
	int	result_row;
	int	result_col;

	i = -1;
	while (++i < texHeight)
	{
		j = -1;
		while (++j < texWidth)
		{
			result_row = (img->height * i) / texHeight;
			result_col = (img->width * j) / texWidth;
			if (result_row < 0)
				result_row = 0;
			if (result_col < 0)
				result_col = 0;
			color = img->addr_tex[img->width * result_row + result_col];
			var->tex[idx].texture[texWidth * i + j] = color;
		}
	}
	var->tex[idx].width = texWidth;
	var->tex[idx].height = texHeight;
}

void	init_texture_direction(char *path, t_data *img, t_var *var, int idx)
{
	t_data	img2;

	var->tex[idx].texture = (int *)ft_calloc(texHeight * texWidth, sizeof(int));
	img2.img = mlx_xpm_file_to_image(img->mlx, path, &img2.width, &img2.height);
	img2.addr_tex = (int *)mlx_get_data_addr \
	(img2.img, &img2.bits_pixel, &img2.line_length, &img2.endian);
	copy_texture(&img2, var, idx);
	mlx_destroy_image(img->mlx, img2.img);
}

void	init_texture(t_data *img, t_var *var)
{
	init_texture_direction(var->map->no, img, var, 0);
	init_texture_direction(var->map->so, img, var, 1);
	init_texture_direction(var->map->we, img, var, 2);
	init_texture_direction(var->map->ea, img, var, 3);
}

void	texture_mapping(t_var *var)
{
	double	wallx;
	int		texX;

	if (var->ray->side == 0)
		wallx = var->vec->pos.y + var->ray->perpWallDist * var->ray->rayDir.y;
	else
		wallx = var->vec->pos.x + var->ray->perpWallDist * var->ray->rayDir.x;
	wallx -= floor((wallx));

	texX = (int)(wallx * (double)var->tex->width);
	if (var->ray->side == 0 && var->ray->rayDir.x > 0)
		texX = var->tex->width - texX - 1;
	if (var->ray->side == 1 && var->ray->rayDir.y < 0)
		texX = var->tex->width - texX - 1;
	var->tex_var.wallx = wallx;
	var->tex_var.texX = texX;
}

void	calculate_direction(t_var *var)
{
	if (var->ray->side == 0 && var->ray->rayDir.x < 0)
		var->tex_var.direction = 0;
	else if (var->ray->side == 0 && var->ray->rayDir.x > 0)
		var->tex_var.direction = 1;
	else if (var->ray->side == 1 && var->ray->rayDir.y < 0)
		var->tex_var.direction = 2;
	else
		var->tex_var.direction = 3;
}

void	draw_texture(t_var *var, int x)
{
	int		texY;
	int		color;
	int		y;

	var->tex_var.step = 1.0 * var->tex->height / var->ray->lineHeight;
	var->tex_var.texPos = (var->ray->drawStart - screenHeight \
	/ 2 + var->ray->lineHeight / 2) * var->tex_var.step;
	while (y < var->ray->drawEnd)
	{
		texY = (int)var->tex_var.texPos & (var->tex->height - 1);
		var->tex_var.texPos += var->tex_var.step;
		color = var->tex[var->tex_var.direction] \
		.texture[var->tex->height * texY + var->tex_var.texX];
		if (var->ray->side == 1)
			color = (color >> 1) & 8355711;
		my_mlx_pixel_put(var->image, x, y, color);
		y++;
	}
}

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
		texture_mapping(var);
		calculate_direction(var);
		draw_texture(var, x);
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

	init_map(argc, argv, &map);
	var.map = &map;

	init_mlx(&image);
	var.image = &image;

	init_texture(&image, &var);


	init_vec_set(&vec, &map);
	ft_memset(&ray, 0, sizeof(t_ray));
	ft_memset(&key, 0, sizeof(t_key));
	init_frame(&frame);

	var.vec = &vec;
	var.key = &key;
	var.frame = &frame;
	var.ray = &ray;

	mlx_hook(image.win_ptr, 2, 0, key_press, &var);
	mlx_hook(image.win_ptr, 3, 1L << 1, key_lift, &var);

	mlx_loop_hook(image.mlx, render, &var);
	mlx_loop(image.mlx);
	exit (0);
}

