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

int	check_valid_line(char *data, char **dict, int *arr)
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
			check_dict++;
		}
		i++;
	}
	if (check_dict == 0)
		return (0);
	return (1);
}

int	check_valid_data(char **data, char **dict, int *arr)
{
	int		i;

	i = 0;
	while (data[i] && !check_same_digit(arr, 1, 6))
	{
		if (!check_valid_line(data[i], dict, arr))
			return (0);
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
	t_cube3d	*cub;
	char	**data_dict;
	int		*array_check;

	data_dict = new_data_dict();
	array_check = new_int_array(6);
	fd = open("map.ber", O_RDONLY);
	matrix = new_map(fd);
	print_map(matrix);
	if (check_valid_data(matrix, data_dict, array_check) == 1)
		printf("Datos están bien\n");
	else
	{
		printf("Datos están mal\n");
		return (1);
	}
	cub = (t_cube3d *)malloc(sizeof(t_cube3d));
	set_textures_colors(cub, matrix, data_dict);
	printf("Termina texturas y colores\n");
	free(data_dict);
	free(array_check);
	free_matrix((void**)matrix);
	int i = -1;
	while (i++ < 4)
		free(cub->textures[i].file);
	free(cub);
	printf("Libera bien\n");
	atexit(&leaks);
	return (0);
}
