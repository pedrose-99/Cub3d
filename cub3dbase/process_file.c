/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 10:45:08 by pfuentes          #+#    #+#             */
/*   Updated: 2023/10/04 11:37:37 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_errors_file(int error)
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
		printf("Mal visual data\n");
		close(fd);
		return (1);
	}
	map = new_map(fd);
	cub->map = normalize_map(map);
	close(fd);
	free_matrix((void **)map);
	map = NULL;
	if (!map_is_close(cub->map))
		return (2);
	return (0);
}
