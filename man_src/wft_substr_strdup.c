/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wft_substr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiko <jiko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 01:57:23 by jiko              #+#    #+#             */
/*   Updated: 2024/02/12 01:58:43 by jiko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

char	*wft_strdup(const char *src)
{
	char	*cp;
	char	*tmp;

	cp = wft_calloc(ft_strlen(src) + 1, 1);
	tmp = cp;
	if (tmp != NULL)
	{
		while (*src)
			*tmp++ = *src++;
		return (cp);
	}
	return (NULL);
}

static char	*wal(char const *s, unsigned int st, size_t len, unsigned int *strl)
{
	char	*tmp;
	int		idx;

	idx = 0;
	if (st >= *strl || !len)
		return (wft_calloc(1, 1));
	else
	{
		if (*strl > st + len)
		{
			tmp = wft_calloc(len + 1, 1);
			while (len--)
				tmp[idx++] = s[st++];
		}
		else
			tmp = (char *)wft_strdup(((char *)s + st));
	}
	return (tmp);
}

char	*wft_substr(char const *s, unsigned int start, size_t len)
{
	char			*tmp;
	unsigned int	strl;

	strl = (unsigned int)ft_strlen(s);
	tmp = wal(s, start, len, &strl);
	return (tmp);
}