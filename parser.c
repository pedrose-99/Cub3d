#include "cub3d.h"

static char	**new_data_dict(void)
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

static int	set_data(t_cub3d *cub3d, char *data, char **dict)
{
	int	check_dict;
	int	i;

	check_dict = -1;
	i = 0;
	if (!*data)
		return (0);
	while (dict[i])
	{
		if (!ft_strncmp(data, dict[i], ft_strlen(dict[i])))
		{
			if (i < 4)
				cub3d->textures[i] = set_texture(cub3d, data);
			else
			{
				cub3d->colors[i - 4] = set_color(data);
				if (!cub3d->colors[i - 4])
					return (-1);
			}
			check_dict = i;
			break ;
		}
		i++;
	}
	return (check_dict);
}

int	set_visual_data(t_cub3d *cub3d, int fd)
{
	int		i;
	char	*line;
	char	**dict;
	int		check;
	int		result;

	dict = new_data_dict();
	i = 0;
	result = 0;
	line = get_next_line_no_nl(fd);
	while (line && result != 15)
	{
		printf("LÍNEA: %s$\n", line);
		check = set_data(cub3d, line, dict);
		free(line);
		if (check == -1)
			return (0);
		result += check;
		line = get_next_line_no_nl(fd);
		i++;
	}
	printf("Result: %d\n", result);
	if (result != 15)
		return (0); // si resultado no es igual a 15, está mal, no encontró los 6 correspondientes de manera única
	return (1);
}

t_cub3d	*set_cub3d(void)
{
	t_cub3d	*cub3d;

	cub3d = (t_cub3d *)malloc(sizeof(t_cub3d));
	cub3d->mlx_ptr = mlx_init();
	cub3d->colors = (t_color **)malloc(sizeof(t_color *) * 2);
	cub3d->textures = (t_texture **)malloc(sizeof(t_texture *) * 4);
	return (cub3d);
}
void	free_cub3d(t_cub3d *cub3d)
{
	int	i;

	printf("Entra a liberar cub3d\n");
	i = 0;
	while (i < 4)
	{
		free(cub3d->textures[i]->file);
		free(cub3d->textures[i]);
		i++;
	}
	free(cub3d->textures);
	printf("Libera bien texturas\n");
	i = 0;
	while (i < 2)
	{
		if (cub3d->colors[i])
			free(cub3d->colors[i]);
		i++;
	}
	free(cub3d->colors);
	printf("Libera bien colores\n");
	free(cub3d);
	printf("Libera bien todo cub3d\n");
}
/*
int	main(void)
{
	char		**matrix;
	int			fd;
	t_cub3d	*cub;

	//set cub3d y texturas/colores

	fd = open("map.ber", O_RDONLY);
	cub = set_cub3d();
	if (set_visual_data(cub, fd) == 1)
		printf("Datos están bien\n");
	else
	{
		printf("Datos están mal\n");
		return (1);
	}
	free_cub3d(cub);
	cub = NULL;
	printf("Libera bien\n");

	//parte del mapa

	matrix = new_map(fd);
	print_matrix(matrix);
	char **normalized = normalize_map(matrix);
	printf("Hace normalized\n");
	print_matrix(normalized);
	free_matrix((void**)matrix);
	free_matrix((void**)normalized);
	printf("Hace bien normalized\n");
	//atexit(&leaks);
	return (0);
}*/
