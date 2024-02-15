/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 05:07:43 by sumjo             #+#    #+#             */
/*   Updated: 2024/02/16 02:35:57 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void move_forward(t_var *var)
{
	int x;
	int y;

	x = (int)(var->vec->pos.x + var->vec->dir.x * var->frame->moveSpeed);
	if (var->map->map[(int)var->vec->pos.y][x] == 0)
		var->vec->pos.x += var->vec->dir.x * var->frame->moveSpeed;
	y = (int)(var->vec->pos.y + var->vec->dir.y * var->frame->moveSpeed);
	if (var->map->map[y][(int)var->vec->pos.x] == 0)
		var->vec->pos.y += var->vec->dir.y * var->frame->moveSpeed;
}

void move_backward(t_var *var)
{
	int x;
	int y;

	x = (int)(var->vec->pos.x - var->vec->dir.x * var->frame->moveSpeed);
	if (var->map->map[(int)var->vec->pos.y][x] == 0)
		var->vec->pos.x -= var->vec->dir.x * var->frame->moveSpeed;
	y = (int)(var->vec->pos.y - var->vec->dir.y * var->frame->moveSpeed);
	if (var->map->map[y][(int)var->vec->pos.x] == 0)
		var->vec->pos.y -= var->vec->dir.y * var->frame->moveSpeed;
}

void move_left(t_var *var)
{
	int x;
	int y;

	x = (int)(var->vec->pos.x - var->vec->plane.x * var->frame->moveSpeed);
	if (var->map->map[(int)var->vec->pos.y][x] == 0)
		var->vec->pos.x -= var->vec->plane.x * var->frame->moveSpeed;
	y = (int)(var->vec->pos.y - var->vec->plane.y * var->frame->moveSpeed);
	if (var->map->map[y][(int)var->vec->pos.x] == 0)
		var->vec->pos.y -= var->vec->plane.y * var->frame->moveSpeed;
}

void move_right(t_var *var)
{
	int x;
	int y;

	x = (int)(var->vec->pos.x + var->vec->plane.x * var->frame->moveSpeed);
	if (var->map->map[(int)var->vec->pos.y][x] == 0)
		var->vec->pos.x += var->vec->plane.x * var->frame->moveSpeed;
	y = (int)(var->vec->pos.y + var->vec->plane.y * var->frame->moveSpeed);
	if (var->map->map[y][(int)var->vec->pos.x] == 0)
		var->vec->pos.y += var->vec->plane.y * var->frame->moveSpeed;
}
