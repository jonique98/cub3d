/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_util_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiko <jiko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:44:23 by jiko              #+#    #+#             */
/*   Updated: 2024/02/28 22:44:41 by jiko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

void	safe_free(void *ptr)
{
	if (ptr)
		free(ptr);
}

char	**double_free(int i, char	**be_return)
{
	while (i != -1)
		free(be_return[i--]);
	free(be_return);
	return (NULL);
}

int	double_free_int(int i, int **be_return)
{
	while (i != -1)
		free(be_return[i--]);
	free(be_return);
	return (0);
}

void	*wft_calloc(int count, int size)
{
	void	*ptr;

	ptr = ft_calloc(count, size);
	if (!ptr)
		ft_exit(1, "Error\nMemory allocation failed\n");
	return (ptr);
}
