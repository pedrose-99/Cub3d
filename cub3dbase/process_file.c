/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pserrano <pserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 10:45:08 by pfuentes          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/08/24 11:27:06 by pserrano         ###   ########.fr       */
=======
<<<<<<< HEAD:process_file.c
/*   Updated: 2023/08/24 09:51:55 by pfuentes         ###   ########.fr       */
=======
/*   Updated: 2023/08/23 14:13:12 by pserrano         ###   ########.fr       */
>>>>>>> 1dfd4f9e952d3b51f01be7605404d9b79a8091e9:cub3dbase/process_file.c
>>>>>>> e51693cdf09b9cecfa609be47f6b3a9d7eeb44c6
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
		exit(1);
	fd = ft_open(file);
	if (fd < 0)
		exit(1);
	*cub3d = set_cub3d();
	cub = *cub3d;
	if (!set_visual_data(cub, fd))
	{
		print_errors_file(1);
		close(fd);
		return (1);
	}
	map = new_map(fd);
	cub->map = normalize_map(map);
	//system("leaks -q cub3d");
	free_matrix((void **)map);
	map = NULL;
	if (!map_is_close(cub->map))
	{
		print_errors_file(2);
		close(fd);
		system("leaks -q cub3d");
		return (2);
	}
	close(fd);
	printf("Process file bien\n");
	return (0);
}
