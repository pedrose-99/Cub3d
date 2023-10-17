/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 12:02:39 by pfuentes          #+#    #+#             */
/*   Updated: 2023/10/16 10:26:38 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	max_array_len_matrix(char **matrix)
{
	int	i;
	int	max;
	int	len;

	i = 0;
	max = 0;
	while (matrix[i])
	{
		len = ft_strlen(matrix[i]);
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}

static char	*copy_fill_array(int new_len, char *arr, char fill)
{
	char	*new_arr;
	int		old_len;
	int		i;

	new_arr = (char *)malloc(new_len + 1);
	old_len = ft_strlen(arr);
	i = 0;
	while (i < old_len)
	{
		new_arr[i] = arr[i];
		i++;
	}
	while (i < new_len)
	{
		new_arr[i] = fill;
		i++;
	}
	new_arr[i] = '\0';
	return (new_arr);
}

static char	*str_same_char(char c, int len)
{
	char	*str;
	int		i;

	str = (char *)malloc(sizeof(char) * len + 1);
	i = 0;
	while (i < len)
	{
		str[i] = c;
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*pad_str(char *str, int len)
{
	char	*padded;
	int		i;

	padded = (char *)malloc(sizeof(char) * len + 3);
	i = 0;
	padded[0] = ' ';
	while (i <= len)
	{
		padded[i + 1] = str[i];
		i++;
	}
	padded[i] = ' ';
	padded[i + 1] = '\0';
	return (padded);
}

char	**normalize_map(char **map)
{
	char	**normalize;
	char	*aux;
	int		max;
	int		i;
	int		j;

	normalize = (char **)malloc(sizeof(char *) * (matrix_len(map) + 3));
	max = max_array_len_matrix(map);
	normalize[0] = str_same_char(' ', max + 2);
	i = 0;
	j = 1;
	while (map[i])
	{
		aux = copy_fill_array(max, map[i], ' ');
		normalize[j] = pad_str(aux, max);
		free(aux);
		i++;
		j++;
	}
	normalize[j] = str_same_char(' ', max + 2);
	normalize[j + 1] = NULL;
	return (normalize);
}
