/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 10:45:08 by pfuentes          #+#    #+#             */
/*   Updated: 2023/09/06 12:36:19 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	print_errors_file(int error)
{
	if (error == 0)
		printf("Error. Invalid file extension\n");
	else if (error == 1)
		printf("Error. Invalid data format\n");
	else if (error == 2)
		printf("Error. Invalid map format\n");
}

static int	valid_file_ext(char *file)
{
	if (!ft_rev_strncmp(file, ".cub", 3))
		return (1);
	print_errors_file(0);
	return (0);
}

int	process_file(t_cub3d **cub3d, char *file)
{
	char	**map;
	int		fd;
	t_cub3d	*cub;

	if (!valid_file_ext(file))
		return (1);
	fd = ft_open(file);
	if (fd < 0)
		return (1);
	*cub3d = set_cub3d();
	cub = *cub3d;
	if (!set_visual_data(cub, fd))
	{
		print_errors_file(1);
		close(fd);
		return (2);
	}
	cub->textures[4] = xpm_to_img(*cub3d, "images/ceilling2.xpm");
	cub->textures[5] = xpm_to_img(*cub3d, "images/floor.xpm");
	cub->textures[6] = xpm_to_img(*cub3d, "images/puertabuena.xpm");
	map = new_map(fd);
	cub->map = normalize_map(map);
	printf("Mapa normalizado\n");
	print_matrix(cub->map);
	free_matrix((void **)map);
	map = NULL;
	if (!map_is_close(cub->map))
	{
		print_errors_file(2);
		close(fd);
		return (3);
	}
	cub->doors = set_doors_lst(cub->map);
	if (!cub->doors)
		printf("No hizo bien lista de puertas\n");
	close(fd);
	return (0);
}
