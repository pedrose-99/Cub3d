/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pserrano <pserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 10:54:33 by pfuentes          #+#    #+#             */
/*   Updated: 2023/08/22 14:23:04 by pserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_cub3d	*set_cub3d(void)
{
	t_cub3d	*cub3d;
	int		i;

	cub3d = (t_cub3d *)malloc(sizeof(t_cub3d));
	cub3d->mlx_ptr = mlx_init();
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

void	free_cub3d(t_cub3d *cub3d)
{
	int	i;

	printf("Entra a liberar cub3d\n");
	i = 0;
	printf("Libera bien texturas\n");
	i = 0;
	/*
	while (i < 2)
	{
		if (cub3d->colors[i])
			free(cub3d->colors[i]);
		i++;
	}*/
	//free(cub3d->colors);
	printf("Libera bien colores\n");
	free(cub3d);
	printf("Libera bien todo cub3d\n");
}
