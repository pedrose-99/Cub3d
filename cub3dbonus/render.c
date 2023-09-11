/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 13:14:35 by pfuentes          #+#    #+#             */
/*   Updated: 2023/09/11 13:39:15 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	select_tex_animate(t_cub3d *cub3d)
{
	static int	frame;
	static int	i;
	int			pos;

	if (frame % 20 == 0)
	{
		printf("Seleccionar texturas\n");
		pos = rand() % 3;
		printf("Pos: %d\n", pos);
		cub3d->select_tex[0] = cub3d->textures[pos];
		pos = rand() % 3;
		printf("Pos: %d\n", pos);
		cub3d->select_tex[1] = cub3d->textures[pos];
		pos = rand() % 3;
		printf("Pos: %d\n", pos);
		cub3d->select_tex[2] = cub3d->textures[pos];
		pos = rand() % 3;
		printf("Pos: %d\n", pos);
		cub3d->select_tex[3] = cub3d->textures[pos];
		i++;
		if (i == 4)
			i = 0;
	}
	frame++;
}

int	render_frame(t_cub3d *cub3d)
{
	mlx_clear_window(cub3d->mlx_ptr, cub3d->win);
	clear_buffer(cub3d);
	select_tex_animate(cub3d);
	floorcaster(cub3d);
	raycaster(cub3d);
	draw_minimap(cub3d);
	mlx_put_image_to_window(cub3d->mlx_ptr, cub3d->win,
		cub3d->buffer.img_ptr, 0, 0);
	return (0);
}

int	render_loop(t_cub3d *cub3d)
{
	check_mouse_move(cub3d, cub3d->player);
	key_funcs(cub3d);
	animate_doors(cub3d, cub3d->doors);
	render_frame(cub3d);
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
