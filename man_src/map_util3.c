/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_util3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiko <jiko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 18:42:50 by jiko              #+#    #+#             */
/*   Updated: 2024/02/27 18:43:04 by jiko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	set_param_if_null(char *line, t_map *map)
{
	if (is_param_full(map) && map->map_height)
	{
		map->map_start--;
		map->map_flag = 1;
	}
	safe_free(line);
}

int	check_valid_string(char **s)
{
	if (!ft_strncmp(s[0], "NO", 3) || !ft_strncmp(s[0], "SO", 3)
		|| !ft_strncmp(s[0], "WE", 3) || !ft_strncmp(s[0], "EA", 3)
		|| !ft_strncmp(s[0], "F", 2) || !ft_strncmp(s[0], "C", 2))
		return (1);
	return (0);
}

void	if_check_vaild_string(char **s, t_map *map, char *line)
{
	if (check_valid_string(s))
		set_param_if_char(map, s);
	else if (is_param_full(map) && is_map(line))
		set_param_elif_char(map, line);
	else
		ft_exit(1, "Error\nInvalid parameter\n");
}