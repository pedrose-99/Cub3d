/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pserrano <pserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:56:55 by pserrano          #+#    #+#             */
/*   Updated: 2023/08/22 13:57:21 by pserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	color_int(int t, int red, int green, int blue)
{
	return (t << 24 | red << 16 | green << 8 | blue);
}

//Arreglar
int	set_color(char	*data)
{
	int		start;
	int		end;
	int		cont;
	char	*color_str;
	int		color[3];

	if (str_char_num(data, ',') != 2)
	{
		printf("Número de comillas distinto de 2\n");
		return (-1);
	}
	start = skip_char(data, ' ', move_to_char(data, ' ', 0));
	cont = 0;
	while (cont < 3)
	{
		end = move_to_char(data, ',', start);
		color_str = ft_substr(data, start, end - start);
		if (!*color_str)
		{
			free(color_str);
			printf("No hay color_str, no hay nada antes de comilla\n");
			return (-1);
		}
		printf("Color_str: %s$\n", color_str);
		if (!ft_str_is_digit(color_str))
		{
			free(color_str);
			printf("Color_str tiene algo que no es dígito\n");
			return (-1);
		}
		color[cont] = ft_atoi(color_str);
		free(color_str);
		if (color[cont] < 0 || color[cont] > 255)
		{
			printf("Se sale del rango\n");
			return (-1);
		}
		start = ++end;
		cont++;
	}
	printf("RED: %d\n", color[0]);
	printf("GREEN: %d\n", color[1]);
	printf("BLUE: %d\n", color[2]);
	return (color_int(0, color[0], color[1], color[2]));
}
