/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_util2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiko <jiko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:47:53 by jiko              #+#    #+#             */
/*   Updated: 2024/02/27 17:54:57 by jiko             ###   ########.fr       */
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
