/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josumin <josumin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 05:07:43 by sumjo             #+#    #+#             */
/*   Updated: 2024/02/27 19:03:46 by josumin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	move_forward(t_var *var)
{
	int	x;
	int	y;

	x = (int)(var->vec->pos.x + var->vec->dir.x * 0.9);
	if (var->map->map[(int)var->vec->pos.y][x] == 0)
		var->vec->pos.x += var->vec->dir.x * var->frame->move_speed;
	y = (int)(var->vec->pos.y + var->vec->dir.y * 0.9);
	if (var->map->map[y][(int)var->vec->pos.x] == 0)
		var->vec->pos.y += var->vec->dir.y * var->frame->move_speed;
}

void	move_backward(t_var *var)
{
	int	x;
	int	y;

	x = (int)(var->vec->pos.x - var->vec->dir.x * 0.9);
	if (var->map->map[(int)var->vec->pos.y][x] == 0)
		var->vec->pos.x -= var->vec->dir.x * var->frame->move_speed;
	y = (int)(var->vec->pos.y - var->vec->dir.y * 0.9);
	if (var->map->map[y][(int)var->vec->pos.x] == 0)
		var->vec->pos.y -= var->vec->dir.y * var->frame->move_speed;
}

void	move_left(t_var *var)
{
	int	x;
	int	y;

	x = (int)(var->vec->pos.x - var->vec->plane.x * 0.5);
	if (var->map->map[(int)var->vec->pos.y][x] == 0)
		var->vec->pos.x -= var->vec->plane.x * var->frame->move_speed;
	y = (int)(var->vec->pos.y - var->vec->plane.y * 0.5);
	if (var->map->map[y][(int)var->vec->pos.x] == 0)
		var->vec->pos.y -= var->vec->plane.y * var->frame->move_speed;
}

void	move_right(t_var *var)
{
	int	x;
	int	y;

	x = (int)(var->vec->pos.x + var->vec->plane.x * 0.5);
	if (var->map->map[(int)var->vec->pos.y][x] == 0)
		var->vec->pos.x += var->vec->plane.x * var->frame->move_speed;
	y = (int)(var->vec->pos.y + var->vec->plane.y * 0.5);
	if (var->map->map[y][(int)var->vec->pos.x] == 0)
		var->vec->pos.y += var->vec->plane.y * var->frame->move_speed;
}
