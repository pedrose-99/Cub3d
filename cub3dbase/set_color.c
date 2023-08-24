/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:56:55 by pserrano          #+#    #+#             */
/*   Updated: 2023/08/23 13:07:28 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	color_int(int t, int red, int green, int blue)
{
	return (t << 24 | red << 16 | green << 8 | blue);
}

static int	valid_format_color(char *data, char **color_matrix)
{
	if (str_char_num(data, ',') != 2 && matrix_len(color_matrix) != 3)
	{
		printf("Error. Incorrect color format\n");
		free_matrix((void **)color_matrix);
		return (0);
	}
	return (1);
}

static int	valid_color(char *data)
{
	int	color;

	if (!*data)
	{
		printf("Error. No color after quote\n");
		return (0);
	}
	if (!ft_str_is_digit(data))
	{
		printf("Error. No numeric characters\n");
		return (0);
	}
	color = ft_atoi(data);
	if (color < 0 || color > 255)
	{
		printf("Error. Color out of range\n");
		return (-1);
	}
	return (color);
}

int	set_color(char	*data)
{
	int		i;
	char	**color_matrix;
	int		color[3];

	color_matrix = ft_split(&data[move_to_char(data, ' ', 0) + 1], ',');
	if (!valid_format_color(data, color_matrix))
		return (-1);
	i = 0;
	while (color_matrix[i])
	{
		color[i] = valid_color(color_matrix[i]);
		if (color[i] == -1)
		{
			free_matrix((void **)color_matrix);
			return (-1);
		}
		i++;
	}
	free_matrix((void **)color_matrix);
	return (color_int(0, color[0], color[1], color[2]));
}
