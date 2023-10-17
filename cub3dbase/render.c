/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 13:14:35 by pfuentes          #+#    #+#             */
/*   Updated: 2023/10/16 10:22:50 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	render_frame(t_cub3d *cub3d)
{
	mlx_clear_window(cub3d->mlx_ptr, cub3d->win);
	clear_buffer(cub3d);
	buffer_ceilling_floor(cub3d);
	raycaster(cub3d);
	return (0);
}

int	render_loop(t_cub3d *cub3d)
{
	key_funcs(cub3d);
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
			cub3d->buffer.data[y * WINDOW_X + x] = cub3d->colors[0];
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
			cub3d->buffer.data[y * WINDOW_X + x] = cub3d->colors[1];
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
