/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiko <jiko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 05:12:08 by sumjo             #+#    #+#             */
/*   Updated: 2024/02/28 20:21:59 by jiko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_exit(int ret, char *str)
{
	if (str)
		ft_putstr_fd(str, 2);
	exit(ret);
}

int	ft_strlen_doble(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}
