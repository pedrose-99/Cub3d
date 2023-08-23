/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 10:54:33 by pfuentes          #+#    #+#             */
/*   Updated: 2023/08/23 09:54:21 by pfuentes         ###   ########.fr       */
/*                                                                            */
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
		mlx_destroy_image(cub3d->mlx_ptr, cub3d->textures[i].img_ptr);
		i++;
	}
}

void	free_cub3d(t_cub3d *cub3d)
{
	printf("Free cub3d\n");
	free_matrix((void **)cub3d->map);
	free_textures(cub3d);
	free(cub3d->player);
	free(cub3d->mlx_ptr);
	free(cub3d->win);
	free(cub3d);
	cub3d = NULL;
}
