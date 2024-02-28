/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiko <jiko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 05:12:32 by sumjo             #+#    #+#             */
/*   Updated: 2024/02/28 22:44:41 by jiko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

int	key_press(int key_code, t_var *var)
{
	if (key_code == 53)
		exit(0);
	else if (key_code == 123)
		var->key->left_rotate = 1;
	else if (key_code == 124)
		var->key->right_rotate = 1;
	else if (key_code == 0)
		var->key->left = 1;
	else if (key_code == 1)
		var->key->backward = 1;
	else if (key_code == 13)
		var->key->forward = 1;
	else if (key_code == 2)
		var->key->right = 1;
	else if (key_code == 125)
		var->key->down = 1;
	else if (key_code == 12)
	{
		if (var->key->mouse_press == 0)
			mouse_press(var);
		else
			mouse_release(var);
	}
	return (0);
}

int	key_lift(int key_code, t_var *var)
{
	if (key_code == 123)
		var->key->left_rotate = 0;
	else if (key_code == 124)
		var->key->right_rotate = 0;
	else if (key_code == 0)
		var->key->left = 0;
	else if (key_code == 1)
		var->key->backward = 0;
	else if (key_code == 13)
		var->key->forward = 0;
	else if (key_code == 2)
		var->key->right = 0;
	else if (key_code == 125)
		var->key->down = 0;
	return (0);
}

int	render(t_var *var)
{
	if (var->key->left_rotate)
		rotate_left(var);
	if (var->key->right_rotate)
		rotate_right(var);
	if (var->key->left)
		move_left(var);
	if (var->key->right)
		move_right(var);
	if (var->key->forward)
		move_forward(var);
	if (var->key->backward)
		move_backward(var);
	if (var->key->mouse_press == 1)
	{
		if (var->key->mouse_x - var->image->width / 2 > 1000)
			rotate_right(var);
		else if (var->key->mouse_x - var->image->width / 2 < -1000)
			rotate_left(var);
	}
	draw(var);
	return (0);
}
