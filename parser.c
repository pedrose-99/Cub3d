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

int	*new_int_array(void)
{
	int	*arr;
	int	i;

	arr = (int *)malloc(sizeof(int) * 6);
	i = 0;
	while (i < 6)
	{
		arr[i] = 0;
		i++;
	}
	return (arr);
}

int	check_same_digit(int *arr, int val, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (arr[i] != val)
			return (0);
		i++;
	}
	return (1);
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

int	skip_char(char *str, char c, int i)
{
	while (str[i] && str[i] == c)
		i++;
	return (i);
}

int	move_to_char(char *str, char c, int i)
{
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

int	str_count_char(char *str, char c)
{
	int	num;
	int	i;

	num = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			num++;
		i++;
	}
	return (num);
}

t_texture	set_texture(int id, char	*data)
{
	t_texture	texture;
	int			space_start;

	texture.id = id;
	space_start = move_to_char(data, ' ', 0);
	texture.file = ft_strtrim(&data[space_start], " ");
	printf("ID: %d, FILE: %s$\n", texture.id, texture.file);
	return (texture);
}
int	set_color(t_color *color, int id, char	*data)
{
	int		start;
	int		end;
	int		cont;
	char	*color_str;

	color->id = id;
	if (str_count_char(data, ',') != 2)
		return (0);
	start = skip_char(data, ' ', move_to_char(data, ' ', 0));
	cont = 0;
	while (cont < 3)
	{
		end = move_to_char(data, ',', start);
		color_str = ft_substr(data, start, end - start);
		color->rgb[cont] = ft_atoi(color_str);
		free(color_str);
		if (color->rgb[cont] < 0 || color->rgb[cont] > 255)
			return (0);
		start = ++end;
		cont++;
	}
	printf("RED: %d\n", color->rgb[0]);
	printf("GREEN: %d\n", color->rgb[1]);
	printf("BLUE: %d\n", color->rgb[2]);
	return (1);
}

int	set_texture_color(t_cube3d *cub, char *data, char **dict)
{
	int	i;

	i = 0;
	if (!*data)
		return (-1);
	while (dict[i])
	{
		if (!ft_strncmp(data, dict[i], ft_strlen(dict[i])))
		{
			if (i < 4)
				cub->textures[i] = set_texture(i, data);
			else
				if (!set_color(&cub->colors[i], i - 4, data))
					return (0);
		}	
			i++;
	}
	return (1);
}

int	set_textures_colors(t_cube3d *cub, char **data, char **dict)
{
	int		i;
	int		count;
	int		check;

	i = 0;
	count = 0;
	while (data[i] && count < 6)
	{
		printf("Línea %d, %s\n", i, data[i]);
		check = set_texture_color(cub, data[i], dict);
		if (check == 1)
			count++;
		else if (check == 0)
			return (0);
		i++;
	}
	return (1);
}

int	main(void)
{
	char		**matrix;
	int			fd;
	t_cube3d	*cub;
	char	**data_dict;
	int		*array_check;

	data_dict = new_data_dict();
	array_check = new_int_array();
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
