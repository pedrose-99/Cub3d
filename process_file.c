/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pserrano <pserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 10:45:08 by pfuentes          #+#    #+#             */
/*   Updated: 2023/08/23 11:57:49 by pserrano         ###   ########.fr       */
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

int	process_file(t_cub3d *cub3d, char *file)
{
	char	**map;
	int		fd;

	if (!valid_file_ext(file))
		return (0);
	fd = ft_open(file);
	if (fd < 0)
		return (0);
	if (!set_visual_data(cub3d, fd))
	{
		print_errors_file(1);
		return (0);
	}
	map = new_map(fd);
	cub3d->map = normalize_map(map);
	free_matrix((void **)map);
	if (!map_is_close(cub3d->map))
	{
		print_errors_file(2);
		return (0);
	}
	return (1);
}
