#include "cub3d.h"

char	**new_data_dict(void)
{
	char	**dict;

	dict = (char **)malloc(sizeof(char *) * 7);
	dict[0] = "NO";
	dict[1] = "SO";
	dict[2] = "WE";
	dict[3] = "EA";
	dict[4] = "F";
	dict[5] = "C";
	dict[6] = NULL;
	return (dict);
}

int	check_valid_line(char *data, char **dict, int *arr, char **tab)
{
	int	check_dict;
	int	i;

	check_dict = 0;
	i = 0;
	if (!*data)
		return (1);
	while (dict[i])
	{
		if (!ft_strncmp(data, dict[i], ft_strlen(dict[i])))
		{
			arr[i]++;
			tab[i] = ft_strdup(data);
			check_dict++;
		}
		i++;
	}
	if (check_dict == 0)
		return (0);
	return (1);
}

int	check_valid_data(char **data, char **dict, int *arr, char **tab)
{
	int		i;

	i = 0;
	while (data[i] && !check_same_digit(arr, 1, 6))
	{
		if (!check_valid_line(data[i], dict, arr, tab))
		{
			free_matrix((void **)tab);
			return (0);
		}
		i++;
	}
	return (1);
}

void	leaks(void)
{
	system("leaks -q cub3d");
}

int	main(void)
{
	char		**matrix;
	int			fd;
	t_cub3d	*cub;
	char	**data_dict;
	int		*array_check;

	data_dict = new_data_dict();
	array_check = new_int_array(6);
	fd = open("map.ber", O_RDONLY);
	matrix = new_map(fd);
	print_matrix(matrix);
	char **tab;
	tab = init_matrix(7);
	if (check_valid_data(matrix, data_dict, array_check, tab) == 1)
		printf("Datos están bien\n");
	else
	{
		printf("Datos están mal\n");
		return (1);
	}
	print_matrix(tab);
	cub = (t_cub3d *)malloc(sizeof(t_cub3d));
	if (!set_textures_colors(cub, tab))
	{
		printf("Texturas y colores mal\n");
		return (1);
	}
	printf("Termina texturas y colores\n");
	free(data_dict);
	free(array_check);
	int i = 0;
	while (i < 4)
	{
		free(cub->textures[i].file);
		i++;
	}
	free(cub);
	free_matrix((void **)tab);
	printf("Libera bien\n");
	char **normalized = normalize_map(matrix);
	print_matrix(normalized);
	free_matrix((void**)matrix);
	free_matrix((void**)normalized);
	atexit(&leaks);
	return (0);
}
