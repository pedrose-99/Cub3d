/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freecub3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:15:13 by pfuentes          #+#    #+#             */
/*   Updated: 2023/10/04 13:16:08 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3dbonus.h"

static void	free_textures(t_cub3d *cub3d)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (cub3d->textures[i].img_ptr)
			mlx_destroy_image(cub3d->mlx_ptr, cub3d->textures[i].img_ptr);
		i++;
	}
}

void	free_cub3d(t_cub3d *cub3d)
{
	free_textures(cub3d);
	mlx_destroy_image(cub3d->mlx_ptr, cub3d->buffer.img_ptr);
	mlx_destroy_window(cub3d->mlx_ptr, cub3d->win);
	free_matrix((void **)cub3d->map);
	cub3d->map = NULL;
}
