/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_util_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiko <jiko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:31:37 by jiko              #+#    #+#             */
/*   Updated: 2024/02/28 22:44:41 by jiko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

int	open_cube(int argc, char **argv, t_map *map)
{
	int	fd;

	if (argc != 2)
		ft_exit(1, "Error\nInvalid number of arguments\n");
	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 5))
		ft_exit(1, "Error\nInvalid file extension\n");
	ft_memset(map, 0, sizeof(t_map));
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_exit(1, "Error\nFailed to open file\n");
	return (fd);
}

int	is_param_full(t_map *map)
{
	return (map->no && map->so && map->we \
	&& map->ea && map->floor && map->ceiling);
}

int	ft_color_atoi(char *str)
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
	int		color;

	s = wft_split(str, ',');
	if (ft_strlen_doble(s) != 3)
		ft_exit(1, "Error\nInvalid color\n");
	color = ft_color_atoi(s[0]) << 16 | ft_color_atoi(s[1]) << 8
		| ft_color_atoi(s[2]);
	double_free(2, s);
	return (color);
}

int	is_map(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != '0' && line[i] != 'S' && line[i] != 'N'\
		&& line[i] != 'W' && line[i] != 'E' && line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}
