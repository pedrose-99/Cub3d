/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pserrano <pserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 10:45:08 by pfuentes          #+#    #+#             */
/*   Updated: 2023/08/24 11:27:06 by pserrano         ###   ########.fr       */
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
	map = new_map(fd);
	cub->map = normalize_map(map);
	//system("leaks -q cub3d");
	free_matrix((void **)map);
	map = NULL;
	if (!map_is_close(cub->map))
	{
		print_errors_file(2);
		close(fd);
		return (3);
	}
	close(fd);
	printf("Process file bien\n");
	return (0);
}
