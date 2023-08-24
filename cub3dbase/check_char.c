/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pserrano <pserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 11:33:45 by pserrano          #+#    #+#             */
/*   Updated: 2023/08/23 11:38:32 by pserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_valid_char(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == '1' || c == '0' || c == ' ')
		return (1);
	return (0);
}

int	not_char_alone(char **map, int i, int j)
{
	if (map[i][j] == '0' || map[i][j] == 'W' || map[i][j] == 'E'
		|| map[i][j] == 'S' || map[i][j] == 'N')
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
