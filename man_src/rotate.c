/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumjo <sumjo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 05:10:55 by sumjo             #+#    #+#             */
/*   Updated: 2024/02/11 05:47:27 by sumjo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	rotate_left(t_var *var)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = var->vec->dir.x;
	var->vec->dir.x = var->vec->dir.x * cos(var->frame->rotSpeed) \
		- var->vec->dir.y * sin(var->frame->rotSpeed);
	var->vec->dir.y = old_dir_x * sin(var->frame->rotSpeed) \
		+ var->vec->dir.y * cos(var->frame->rotSpeed);
	old_plane_x = var->vec->plane.x;
	var->vec->plane.x = var->vec->plane.x * cos(var->frame->rotSpeed) \
		- var->vec->plane.y * sin(var->frame->rotSpeed);
	var->vec->plane.y = old_plane_x * sin(var->frame->rotSpeed) \
		+ var->vec->plane.y * cos(var->frame->rotSpeed);
}

void	rotate_right(t_var *var)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = var->vec->dir.x;
	var->vec->dir.x = var->vec->dir.x * cos(-var->frame->rotSpeed) \
		- var->vec->dir.y * sin(-var->frame->rotSpeed);
	var->vec->dir.y = old_dir_x * sin(-var->frame->rotSpeed) \
		+ var->vec->dir.y * cos(-var->frame->rotSpeed);
	old_plane_x = var->vec->plane.x;
	var->vec->plane.x = var->vec->plane.x * cos(-var->frame->rotSpeed) \
		- var->vec->plane.y * sin(-var->frame->rotSpeed);
	var->vec->plane.y = old_plane_x * sin(-var->frame->rotSpeed) \
		+ var->vec->plane.y * cos(-var->frame->rotSpeed);
}
