/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 12:06:04 by pfuentes          #+#    #+#             */
/*   Updated: 2023/08/01 09:51:35 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

char	**realloc_matrix(char **matrix, int len)
{
	char	**new_matrix;
	int		i;
	int		prev_len;

	new_matrix = (char **)malloc(sizeof(char *) * len);
	i = 0;
	prev_len = matrix_len(matrix);
	while (i < prev_len)
	{
		new_matrix[i] = matrix[i];
		i++;
	}
	while (i < len)
	{
		new_matrix[i] = NULL;
		i++;
	}
	free(matrix);
	return (new_matrix);
}

char	**init_matrix(char **matrix, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		matrix[i] = NULL;
		i++;
	}
	return (matrix);
}

char	**new_map(int fd)
{
	int		i;
	char	**map;
	char	*line;

	i = 0;
	map = (char **)malloc(sizeof(char *) * 2);
	map = init_matrix(map, 2);
	line = get_next_line(fd);
	while (line)
	{
		map[i] = line;
		if (map[i][ft_strlen(line) - 1] == '\n')
		{
			map[i] = ft_substr(line, 0, ft_strlen(line) - 1);
			free(line);
		}
		i++;
		line = get_next_line(fd);
		if (line)
			map = realloc_matrix(map, i + 2);
	}
	map[i] = NULL;
	return (map);
}

void	print_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}
}

void	leaks(void)
{
	system("leaks -q cub3d");
}

int	char_alone_f(char **map, int i, int j)
{
	if (map[i][j] == ' ')
		return (1);
	if (map[i][j] == '0' || map[i][j] == 'W' || map[i][j] == 'E'
		|| map[i][j] == 'S' || map[i][j] == 'N')
		return (0);
	else
	{
		if (map[i][j] == '1')
		{
			if (j == 0)
			{
				if (map[i + 1][j] == ' ' && map[i][j + 1] == ' ')
					return (0);
			}
		}
		else
		{
			if (map[i + 1][j] == ' ' && map[i][j + 1] == ' '
				&& map[i][j - 1] == ' ')
				return (0);
		}
	}
	return (1);
}

int	char_alone_l(char **map, int i, int j)
{
	if (j == 0)
	{
		if (map[i - 1][j] == ' ' && map[i][j + 1] == ' ')
			return (0);
	}
	else 
	{
		if (map[i - 1][j] == ' ' && map[i][j + 1] == ' ' && map[i][j - 1] == ' ')
			return (0);
	}
	return (1);
}

//Checkear la 1 linea y la ultima
int	not_char_alone(char **map, int i, int j)
{
	if (i == 0)
		return (char_alone_f(map, i, j));
	if (!map[i + 1])
		return (char_alone_l(map, i, j));
	if (map[i][j] == ' ')
		return (1);
	if (map[i][j] == '0' || map[i][j] == 'W' || map[i][j] == 'E'
		|| map[i][j] == 'S' || map[i][j] == 'N')
	{
		if (map[i + 1][j] == ' ' || map[i - 1][j] == ' '
			|| map[i][j + 1] == ' ' || map[i][j - 1] == ' ')
			return (0);
	}
	else
	{
		if (map[i + 1][j] == ' ' && map[i - 1][j] == ' '
			&& map[i][j + 1] == ' ' && map[i][j - 1] == ' ')
			return (0);
	}
	return (1);
}

int	check_first_and_last_line(char **map)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	while (j < (int)ft_strlen(map[0]))
	{
		if (map[0][j] != '1' && map[0][j] != ' ')
			return (0);
		j++;
	}
	while (map[i])
		i++;
	i--;
	j = 0;
	while (j < (int)ft_strlen(map[i]))
	{
		if (map[i][j] != '1' && map[i][j] != ' ')
			return (0);
		j++;
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

int	check_map_hor(char **map, int i, int j)
{
	if (j == 0)
	{
		if (map[i][j] != ' ' && map[i][j] != '1')
			return (0);
	}
	else if (j == (int)ft_strlen(map[i]) - 1)
	{
		if (map[i][j] != '1')
			return (0);
	}
	else
	{
		if (map[i][j] == ' ')
			if (map[i][j - 1] != '1' && map[i][j - 1] != ' ')
				return (0);
		if (map[i][j] == ' ')
			if (map[i][j + 1] != '1' && map[i][j + 1] != ' ')
				return (0);
	}
	return (1);
}

static int	check_map_ver(char **map, int i, int j)
{
	if (map[i + 1])
	{
		if (j <= (int)ft_strlen(map[i + 1]) - 1)
		{
			if (map[i + 1][j] == ' ')
				if (map[i][j] != '1' && map[i][j] != ' ')
					return (0);
			if (map[i][j] == ' ')
				if (map[i + 1][j] != '1' && map[i + 1][j] != ' ')
					return (0);
		}
		else
			if (map[i][j] != '1')
				return (0);
	}
	if (i != 0)
		if (j > (int)ft_strlen(map[i - 1]) - 1 && map[i][j] != '1')
			return (0);
	return (1);
}

int	ft_valid_char(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == '1' || c == '0' || c == ' ')
		return (1);
	return (0);
}

int check_char(char **map)
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

int	ft_isspace(char *line)
{
	int	i;

	i = 0;
	if (line[i] == '\n')
		return (0);
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	return (i);
}

int	check_is_empty(char *line)
{
	int	i;

	i = ft_isspace(line);
	if (line[i] == '\n')
		return (1);
	return (0); 
}
/*
void	check_info_map(char *line, t_cube3d cub, int identifier)
{
	int	i;

	i = ft_isspace(line);
}*/

int	main(void)
{
	char		**matrix;
	int			fd;
	char		*line;
	//t_cube3d	cub;

	atexit(&leaks);
	fd = open("map2.ber", O_RDONLY);
	int	i = 0;

	while (i < 8)
	{
		line = get_next_line(fd);
		free(line);
		i++;
	}
	matrix = new_map(fd);
	print_map(matrix);
	if (map_is_close(matrix))
		printf("Mapa bueno\n");
	else
		printf("Mapa malo\n");
	free_matrix((void **)matrix);
	return (0);
}
