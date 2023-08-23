/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pserrano <pserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 12:06:04 by pfuentes          #+#    #+#             */
/*   Updated: 2023/08/23 11:38:40 by pserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_first_and_last_line(char **map)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	while (map[i][j])
	{
		if (map[i][j] != '1' && map[i][j] != ' ')
			return (0);
		j++;
	}
	while (map[i])
		i++;
	i--;
	j = 0;
	while (map[i][j])
	{
		if (map[i][j] != '1' && map[i][j] != ' ')
			return (0);
		j++;
	}
	return (1);
}

int	check_map_hor(char **map, int i, int j)
{
	if (j == 0 || (j == (int)ft_strlen(map[i]) - 1))
	{
		if (map[i][j] != ' ' && map[i][j] != '1')
			return (0);
	}
	else
	{
		if (map[i][j] == ' ')
		{
			if (map[i][j - 1] != '1' && map[i][j - 1] != ' ')
				return (0);
			if (map[i][j + 1] != '1' && map[i][j + 1] != ' ')
				return (0);
		}
	}
	return (1);
}

static int	check_map_ver(char **map, int i, int j)
{
	if (i == 0 || !map[i + 1])
	{
		if (map[i][j] != ' ' && map[i][j] != '1')
			return (0);
	}
	else
	{
		if (map[i][j] == ' ')
		{
			if (map[i - 1][j] != '1' && map[i - 1][j] != ' ')
				return (0);
			if (map[i + 1][j] != '1' && map[i + 1][j] != ' ')
				return (0);
		}
	}
	return (1);
}

int	first_check_map(char **map)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	start = 0;
	if (!check_first_and_last_line(map))
		return (0);
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!not_char_alone(map, i, j))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	map_is_close(char **map)
{
	int	i;
	int	j;

	i = 0;
	if (!first_check_map(map) || !check_char(map))
		return (0);
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!check_map_hor(map, i, j) || !check_map_ver(map, i, j))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
