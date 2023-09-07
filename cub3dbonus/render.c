/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 13:14:35 by pfuentes          #+#    #+#             */
/*   Updated: 2023/09/07 11:26:40 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	render_frame(t_cub3d *cub3d)
{
	mlx_clear_window(cub3d->mlx_ptr, cub3d->win);
	clear_buffer(cub3d);
	floorcaster(cub3d);
	raycaster(cub3d);
	draw_minimap(cub3d);
	mlx_put_image_to_window(cub3d->mlx_ptr, cub3d->win,
		cub3d->buffer.img_ptr, 0, 0);
	return (0);
}

int	render_loop(t_cub3d *cub3d)
{
	key_funcs(cub3d);
	animate_doors(cub3d, cub3d->doors);
	render_frame(cub3d);
	/*if (cub3d->frame > 100)
	{
		animate_doors(cub3d, cub3d->doors);
		cub3d->frame = 0;
	}
	cub3d->frame++;*/
	return (0);
}

void	buffer_ceilling_floor(t_cub3d *cub3d)
{
	int	x;
	int	y;

	y = 0;
	while (y < WINDOW_Y / 2)
	{
		x = 0;
		while (x < WINDOW_X)
		{
			cub3d->buffer.data[y * WINDOW_X + x] = cub3d->colors[1];
			x++;
		}
		y++;
	}
	y = WINDOW_Y / 2;
	while (y < WINDOW_Y)
	{
		x = 0;
		while (x < WINDOW_X)
		{
			cub3d->buffer.data[y * WINDOW_X + x] = cub3d->colors[0];
			x++;
		}
		y++;
	}
}

void	clear_buffer(t_cub3d *cub3d)
{
	int	i;
	int	size;

	i = 0;
	size = WINDOW_X * WINDOW_Y;
	while (i < size)
	{
		cub3d->buffer.data[i] = 0;
		i++;
	}
}
