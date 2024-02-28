/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiko <jiko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 19:00:50 by josumin           #+#    #+#             */
/*   Updated: 2024/02/28 22:44:41 by jiko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

int	mouse_event_draw(int x, int y, t_var *var)
{
	var->key->mouse_x = x;
	var->key->mouse_y = y;
	return (0);
}

int	mouse_press(t_var *var)
{
	var->key->mouse_press = 1;
	mlx_mouse_hide();
	return (0);
}

int	mouse_release(t_var *var)
{
	var->key->mouse_press = 0;
	mlx_mouse_show();
	return (0);
}
