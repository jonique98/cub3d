/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiko <jiko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 19:51:56 by jiko              #+#    #+#             */
/*   Updated: 2024/02/12 02:55:56 by jiko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	*tmp;
	unsigned char	tmpc;

	tmpc = (unsigned char)c;
	tmp = (unsigned char *)s;
	if (s == NULL)
		return (NULL);
	if (tmpc == 0)
		return ((char *)&tmp[ft_strlen((const char *)tmp)]);
	while (*tmp)
	{
		if (*tmp == tmpc)
			return ((char *)tmp);
		tmp++;
	}
	return (NULL);
}
