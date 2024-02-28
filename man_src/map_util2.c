/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_util2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiko <jiko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:47:53 by jiko              #+#    #+#             */
/*   Updated: 2024/02/28 22:07:46 by jiko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	dfs(t_map *map, int **visited, int x, int y)
{
	if (x < 0 || y < 0 || x >= map->map_height || y >= map->map_width)
		ft_exit(1, "Error\nInvalid map\n");
	if (map->map[x][y] == 1 || visited[x][y])
		return ;
	if (map->map[x][y] == 2)
		ft_exit(1, "Error\nInvalid map\n");
	visited[x][y] = 1;
	dfs(map, visited, x + 1, y);
	dfs(map, visited, x - 1, y);
	dfs(map, visited, x, y + 1);
	dfs(map, visited, x, y - 1);
}

void	dfs_valid_map(t_map *map)
{
	int	**visited;
	int	i;
	int	j;

	visited = wft_calloc(map->map_height, sizeof(int *));
	i = -1;
	while (++i < map->map_height)
		visited[i] = wft_calloc(map->map_width, sizeof(int));
	i = -1;
	while (++i < map->map_height)
	{
		j = -1;
		while (++j < map->map_width)
		{
			if (map->map[i][j] == 0 && !visited[i][j])
				dfs(map, visited, i, j);
		}
	}
	double_free_int(map->map_height - 1, visited);
}

void	remove_space_side(char **line, t_map *map)
{
	int		i;
	int		len;
	char	*tmp;

	i = 0;
	if (!(*line))
		return ;
	tmp = (*line);
	len = ft_strlen((*line));
	if (len == 0)
		return ;
	while (!is_param_full(map) && (*line)[i] == ' ')
		i++;
	if (len == i)
	{
		free(*line);
		*line = wft_calloc(1, sizeof(char));
		return ;
	}
	while ((*line)[len - 1] == ' ')
		len--;
	*line = wft_substr(*line, i, len - i);
	free(tmp);
}

void	set_param_if_char(t_map *map, char **s)
{
	if (ft_strlen_doble(s) != 2)
		ft_exit(1, "Error\nInvalid parameter\n");
	else if (!ft_strncmp(s[0], "NO", 3) && !map->no)
		map->no = wft_strdup(s[1]);
	else if (!ft_strncmp(s[0], "SO", 3) && !map->so)
		map->so = wft_strdup(s[1]);
	else if (!ft_strncmp(s[0], "WE", 3) && !map->we)
		map->we = wft_strdup(s[1]);
	else if (!ft_strncmp(s[0], "EA", 3) && !map->ea)
		map->ea = wft_strdup(s[1]);
	else if (!ft_strncmp(s[0], "F", 2) && !map->floor)
		map->floor = ft_color(s[1]);
	else if (!ft_strncmp(s[0], "C", 2) && !map->ceiling)
		map->ceiling = ft_color(s[1]);
	else
		ft_exit(1, "Error\nInvalid parameter\n");
}

void	set_param_elif_char(t_map *map, char *line)
{
	map->map_start--;
	if (map->map_flag)
		ft_exit(1, "Error\nInvalid map\n");
	map->map_height++;
	map->map_width = ft_max(map->map_width, ft_strlen(line));
}
