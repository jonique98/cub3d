/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josumin <josumin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 05:12:08 by sumjo             #+#    #+#             */
/*   Updated: 2024/02/16 10:15:58 by josumin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	get_time(void)
{
	struct timeval	time;
	int				ret;

	ret = gettimeofday(&time, NULL);
	if (ret == -1)
		return (0);
	return (time.tv_sec * 1000000 + time.tv_usec);
}

void safe_free(void *ptr)
{
	if (ptr)
		free(ptr);
}

int ft_exit(int ret, char *str)
{
	if (str)
		ft_putstr_fd(str, 2);
	exit(ret);
}

int ft_strlen_doble(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	**double_free(int i, char	**be_return)
{
	while (i != -1)
		free(be_return[i--]);
	free(be_return);
	return (NULL);
}

void	*wft_calloc(int count, int size)
{
	void	*ptr;

	ptr = ft_calloc(count, size);
	if (!ptr)
		ft_exit(1, "Error\nMemory allocation failed\n");
	return (ptr);
}

int ft_color_atoi(char *str)
{
	int	i;
	int	num;

	i = 0;
	num = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			ft_exit(1, "Error\nInvalid color\n");
		num = num * 10 + (str[i] - '0');
		if (num < 0 || num > 255)
			ft_exit(1, "Error\nInvalid color\n");
		i++;
	}
	return (num);
}

int	ft_color(char *str)
{
	char	**s;
	int 	color;

	s = wft_split(str, ',');
	if (ft_strlen_doble(s) != 3)
		ft_exit(1, "Error\nInvalid color\n");
	color = ft_color_atoi(s[0]) << 16 | ft_color_atoi(s[1]) << 8 | ft_color_atoi(s[2]);
	double_free(2, s);
	return (color);
}

int ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}
