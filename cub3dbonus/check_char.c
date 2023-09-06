/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 11:33:45 by pserrano          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/09/05 13:16:12 by pfuentes         ###   ########.fr       */
=======
/*   Updated: 2023/09/06 09:32:13 by pserrano         ###   ########.fr       */
>>>>>>> origin/develop
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_valid_char(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W'
<<<<<<< HEAD
		|| c == '1' || c == '0' || c == ' ' || c == 'D')
=======
		|| c == '1' || c == '0' || c == ' ' || c == 'P')
>>>>>>> origin/develop
		return (1);
	return (0);
}

int	not_char_alone(char **map, int i, int j)
{
	if (map[i][j] == '0' || map[i][j] == 'W' || map[i][j] == 'E'
		|| map[i][j] == 'S' || map[i][j] == 'N' || map[i][j] == 'P')
	{
		if (map[i + 1][j] == ' ' || map[i - 1][j] == ' '
			|| map[i][j + 1] == ' ' || map[i][j - 1] == ' ')
			return (0);
	}
	return (1);
}

int	check_char(char **map)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	start = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!ft_valid_char(map[i][j]))
				return (0);
			if (map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'E' || map[i][j] == 'W')
				start++;
			j++;
		}
		i++;
	}
	if (start == 1)
		return (1);
	return (0);
}

int	check_door_wall(char **map, int i, int j)
{
	if (map[i - 1][j] == '1')
	{
		if (map[i + 1][j] == '1' && map[i][j - 1] == '0'
			&& map[i][j + 1] == '0')
			return (1);
	}
	else if (map[i][j - 1] == '1')
	{
		if (map[i][j + 1] == '1' && map[i - 1][j] == '0'
			&& map[i + 1][j] == '0')
			return (1);
	}
	return (0);
}

int	check_door(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'P')
			{
				if (!check_door_wall(map, i, j))
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}
//colision muros y mover camara con raton (funcion mlx)