/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 05:07:43 by sumjo             #+#    #+#             */
/*   Updated: 2024/02/11 05:43:33 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	move_forward(t_var *var)
{
	int	x;
	int	y;

	x = (int)(var->vec->pos.x + var->vec->dir.x * var->frame->moveSpeed);
	y = (int)(var->vec->pos.y);
	if (var->map->map[x][y] == 0)
		var->vec->pos.x += var->vec->dir.x * var->frame->moveSpeed;
	x = (int)(var->vec->pos.x);
	y = (int)(var->vec->pos.y + var->vec->dir.y * var->frame->moveSpeed);
	if (var->map->map[x][y] == 0)
		var->vec->pos.y += var->vec->dir.y * var->frame->moveSpeed;
}

void	move_backward(t_var *var)
{
	int	x;
	int	y;

	x = (int)(var->vec->pos.x - var->vec->dir.x * var->frame->moveSpeed);
	y = (int)(var->vec->pos.y);
	if (var->map->map[x][y] == 0)
		var->vec->pos.x -= var->vec->dir.x * var->frame->moveSpeed;
	x = (int)(var->vec->pos.x);
	y = (int)(var->vec->pos.y - var->vec->dir.y * var->frame->moveSpeed);
	if (var->map->map[x][y] == 0)
		var->vec->pos.y -= var->vec->dir.y * var->frame->moveSpeed;
}

void	move_left(t_var *var)
{
	int	x;
	int	y;

	x = (int)(var->vec->pos.x - var->vec->dir.y * var->frame->moveSpeed);
	y = (int)var->vec->pos.y;
	if (var->map->map[x][y] == 0)
		var->vec->pos.x -= var->vec->dir.y * var->frame->moveSpeed;
	x = (int)var->vec->pos.x;
	y = (int)(var->vec->pos.y + var->vec->dir.x * var->frame->moveSpeed);
	if (var->map->map[x][y] == 0)
		var->vec->pos.y += var->vec->dir.x * var->frame->moveSpeed;
}

void	move_right(t_var *var)
{
	int	x;
	int	y;

	x = (int)(var->vec->pos.x + var->vec->dir.y * var->frame->moveSpeed);
	y = (int)var->vec->pos.y;
	if (var->map->map[x][y] == 0)
		var->vec->pos.x += var->vec->dir.y * var->frame->moveSpeed;
	x = (int)var->vec->pos.x;
	y = (int)(var->vec->pos.y - var->vec->dir.x * var->frame->moveSpeed);
	if (var->map->map[x][y] == 0)
		var->vec->pos.y -= var->vec->dir.x * var->frame->moveSpeed;
}