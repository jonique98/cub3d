/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiko <jiko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 00:06:24 by jiko              #+#    #+#             */
/*   Updated: 2024/02/27 18:43:54 by jiko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	set_param(int fd, t_map *map)
{
	char	*line;
	char	**s;
	int		ret;

	while (42)
	{
		ret = get_next_line(fd, &line);
		if (ret <= 0)
			break ;
		map->map_start++;
		remove_space_side(&line, map);
		if (line == NULL || line[0] == '\0')
		{
			set_param_if_null(line, map);
			continue ;
		}
		s = wft_split(line, ' ');
		if_check_vaild_string(s, map, line);
		free(line);
		double_free(ft_strlen_doble(s), s);
	}
	if (ret == -1)
		ft_exit(1, "Error\nFailed to read file\n");
}

void	set_player_position(t_map *map, int i, int j, char c)
{
	if (map->player_dir)
		ft_exit(1, "Error\nInvalid map\n");
	map->player_x = j;
	map->player_y = i;
	map->player_dir = c;
}

void	set_map_start(int fd, t_map *t_map, int ***map, char *line)
{
	int		i;
	int		j;

	i = -1;
	while (++i < t_map->map_height)
	{
		get_next_line(fd, &line);
		remove_space_side(&line, t_map);
		j = -1;
		while (++j < (int)ft_strlen(line))
		{
			if (line[j] == '1')
				(*map)[i][j] = 1;
			else if (line[j] == '0')
				(*map)[i][j] = 0;
			else if (line[j] == 'N' || line[j] == 'S'
				|| line[j] == 'W' || line[j] == 'E')
				set_player_position(t_map, i, j, line[j]);
		}
		free(line);
	}
	if (!t_map->player_dir)
		ft_exit(1, "Error\nInvalid map\n");
}

static void	set_map(int fd, t_map *t_map)
{
	int		**map;
	char	*line;
	int		i;
	int		j;

	map = wft_calloc(t_map->map_height, sizeof(int *));
	i = -1;
	while (++i < t_map->map_height)
		map[i] = wft_calloc(t_map->map_width, sizeof(int));
	i = -1;
	while (++i < t_map->map_height)
	{
		j = -1;
		while (++j < t_map->map_width)
			map[i][j] = 2;
	}
	i = -1;
	while (++i < t_map->map_start)
	{
		get_next_line(fd, &line);
		free(line);
	}
	set_map_start(fd, t_map, &map, line);
	t_map->map = map;
}

void	init_map(int argv, char **argc, t_map *map)
{
	int	fd;

	fd = open_cube(argv, argc, map);
	set_param(fd, map);
	close(fd);
	if (!is_param_full(map) || !map->map_height || !map->map_width)
		ft_exit(1, "Error\nInvalid map\n");
	fd = open(argc[1], O_RDONLY);
	set_map(fd, map);
	close(fd);
	dfs_valid_map(map);
}
