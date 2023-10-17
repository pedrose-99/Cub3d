/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 10:54:33 by pfuentes          #+#    #+#             */
/*   Updated: 2023/10/16 09:32:02 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */

#include "cub3d.h"

t_cub3d	*set_cub3d(void)
{
	t_cub3d	*cub3d;
	int		i;

	cub3d = (t_cub3d *)malloc(sizeof(t_cub3d));
	cub3d->mlx_ptr = mlx_init();
	cub3d->win = mlx_new_window(cub3d->mlx_ptr, WINDOW_X, WINDOW_Y, "cub3d");
	cub3d->buffer.img_ptr = mlx_new_image(cub3d->mlx_ptr, WINDOW_X, WINDOW_Y);
	cub3d->buffer.data = (int *)mlx_get_data_addr(cub3d->buffer.img_ptr,
			&cub3d->buffer.bpp, &cub3d->buffer.size_l, &cub3d->buffer.endian);
	i = 0;
	while (i < 6)
	{
		cub3d->keys[i] = 0;
		i++;
	}
	return (cub3d);
}

void	free_textures(t_cub3d *cub3d)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (cub3d->textures[i].img_ptr)
			mlx_destroy_image(cub3d->mlx_ptr, cub3d->textures[i].img_ptr);
		i++;
	}
}

void	free_mlx_data(t_cub3d *cub3d)
{
	mlx_destroy_image(cub3d->mlx_ptr, cub3d->buffer.img_ptr);
	mlx_destroy_window(cub3d->mlx_ptr, cub3d->win);
}

void	free_map(t_cub3d *cub3d)
{
	free_matrix((void **)cub3d->map);
	cub3d->map = NULL;
}

void	free_cub3d(t_cub3d *cub3d, int start, int end)
{
	void	(*funcs[4])(t_cub3d*);

	funcs[0] = free_textures;
	funcs[1] = free_mlx_data;
	funcs[2] = free_map;
	funcs[3] = NULL;
	while (funcs[start] && start <= end)
	{
		(*funcs[start])(cub3d);
		start++;
	}
}
