#include "cub3d.h"

char	**realloc_matrix(char **matrix, int len)
{
	char	**new_matrix;
	int		i;
	int		prev_len;

	new_matrix = init_matrix(len);
	i = 0;
	prev_len = matrix_len(matrix);
	while (i < prev_len)
	{
		new_matrix[i] = matrix[i];
		i++;
	}
	free(matrix);
	return (new_matrix);
}

char	**init_matrix(int len)
{
	char	**matrix;
	int		i;

	matrix = (char **)malloc(sizeof(char *) * len);
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

	map = (char **)malloc(sizeof(char *) * 3);
	map = init_matrix(3);
	line = get_next_line_no_nl(fd);
	map[0] = ft_strdup(" ");
	i = 1;
	while (line)
	{
		map[i] = ft_strjoin(" ", line);
		free(line);
		i++;
		line = get_next_line_no_nl(fd);
		if (line)
			map = realloc_matrix(map, i + 2);
	}
	map[i] = NULL;
	return (map);
}

void	print_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		printf("%s$\n", matrix[i]);
		i++;
	}
}
