/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiko <jiko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 20:26:01 by jiko              #+#    #+#             */
/*   Updated: 2024/02/28 22:44:41 by jiko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

static char	*ft_strjoin_2(char *s1, char *s2, int flag)
{
	char	*dest;
	int		i;
	int		j;

	i = -1;
	j = 0;
	if (flag)
		s1 = (char *)wft_calloc(1, sizeof(char));
	dest = (char *)wft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	while (s1[++i])
		dest[i] = s1[i];
	free(s1);
	while (s2[j])
		dest[i++] = s2[j++];
	return (dest);
}

static char	*ft_get_line(char **str, int *i)
{
	char	*dest;

	*i = 0;
	while ((*str)[*i] && (*str)[*i] != '\n')
		(*i)++;
	if ((*str)[*i] == '\0')
	{
		dest = ft_strjoin_2(0, (*str), 1);
		if (!dest)
			return (NULL);
		return (dest);
	}
	dest = (char *)wft_calloc(*i + 2, sizeof(char));
	*i = 0;
	while ((*str)[*i] != '\n')
		dest[(*i)++] = (*str)[*i];
	(*i)++;
	return (dest);
}

static int	freeing(char **str, char *buf, char *dest)
{
	if (buf)
		free(buf);
	if (dest)
		free(dest);
	if (!str)
		return (0);
	if (*str)
	{
		free(*str);
		*str = 0;
	}
	return (0);
}

static int	readline(int fd, int *i, char **str)
{
	char	*buf;

	*i = 1;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (freeing(str, NULL, NULL));
	buf = (char *)wft_calloc(BUFFER_SIZE + 1, sizeof(char));
	while (*i > 0)
	{
		if (ft_strchr(*str, '\n'))
			break ;
		*i = read(fd, buf, BUFFER_SIZE);
		if ((!(*str) && *i == 0))
			return (freeing(str, buf, NULL) + 2);
		if (*i < 0)
			return (freeing(str, buf, NULL));
		buf[*i] = '\0';
		*str = ft_strjoin_2(*str, buf, !(*str));
	}
	freeing(&buf, NULL, NULL);
	return (1);
}

int	get_next_line(int fd, char **dest)
{
	static char	*str;
	char		*buf;
	int			i;
	int			flag;

	buf = NULL;
	flag = readline(fd, &i, &str);
	if (!flag)
		return (-1);
	if (flag == 2)
		return (0);
	*dest = ft_get_line(&str, &i);
	if (*dest && (ft_strlen(str) != ft_strlen(*dest)))
	{
		buf = ft_strjoin_2(NULL, str + i, 1);
		if (!buf)
			return (freeing(&str, NULL, *dest));
	}
	free(str);
	str = buf;
	return (1);
}
