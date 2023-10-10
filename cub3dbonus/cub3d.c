/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 10:54:33 by pfuentes          #+#    #+#             */
/*   Updated: 2023/10/04 13:34:35 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3dbonus.h"

static char	**set_map(int fd)
{
	char	**map;
	char	**norm_map;

	map = new_map(fd);
	norm_map = normalize_map(map);
	free_matrix((void **)map);
	map = NULL;
	if (!map_is_close(norm_map))
	{
		printf("Bad map format\n");
		free_matrix((void **)norm_map);
		return (NULL);
	}
	return (norm_map);
}

static void	set_textures(t_cub3d *cub3d)
{
	cub3d->textures[0] = xpm_to_img(cub3d, "images/northA.xpm");
	cub3d->textures[1] = xpm_to_img(cub3d, "images/northB.xpm");
	cub3d->textures[2] = xpm_to_img(cub3d, "images/PAPER.xpm");
	cub3d->textures[3] = xpm_to_img(cub3d, "images/east_west.xpm");
	cub3d->textures[4] = xpm_to_img(cub3d, "images/ceilling.xpm");
	cub3d->textures[5] = xpm_to_img(cub3d, "images/floor.xpm");
	cub3d->textures[6] = xpm_to_img(cub3d, "images/puertabuena.xpm");
}

static void	set_mlx(t_cub3d *cub3d)
{
	cub3d->mlx_ptr = mlx_init();
	cub3d->win = mlx_new_window(cub3d->mlx_ptr, WINDOW_X, WINDOW_Y, "cub3d");
	cub3d->buffer.img_ptr = mlx_new_image(cub3d->mlx_ptr, WINDOW_X, WINDOW_Y);
	cub3d->buffer.data = (int *)mlx_get_data_addr(cub3d->buffer.img_ptr,
			&cub3d->buffer.bpp, &cub3d->buffer.size_l, &cub3d->buffer.endian);
}

static void	set_select_textures(t_cub3d *cub3d)
{
	cub3d->select_tex[0] = cub3d->textures[0];
	cub3d->select_tex[1] = cub3d->textures[2];
	cub3d->select_tex[2] = cub3d->textures[3];
	cub3d->select_tex[3] = cub3d->textures[3];
	cub3d->select_tex[4] = cub3d->textures[4];
	cub3d->select_tex[5] = cub3d->textures[5];
	cub3d->select_tex[6] = cub3d->textures[6];
}

t_cub3d	*set_cub3d(char *file)
{
	t_cub3d	*cub3d;
	int		fd;
	char	**map;
	int		i;

	fd = open(file, O_RDONLY);
	map = set_map(fd);
	close(fd);
	if (!map)
		return (NULL);
	cub3d = (t_cub3d *)malloc(sizeof(t_cub3d));
	cub3d->map = map;
	set_mlx(cub3d);
	set_textures(cub3d);
	set_select_textures(cub3d);
	set_player(&cub3d->player, cub3d->map);
	cub3d->doors = set_doors_lst(cub3d->map);
	i = 0;
	while (i < 7)
	{
		cub3d->keys[i] = 0;
		i++;
	}
	return (cub3d);
}
