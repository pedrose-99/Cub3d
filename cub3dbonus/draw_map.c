/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 09:53:49 by pfuentes          #+#    #+#             */
/*   Updated: 2023/10/04 13:38:49 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3dbonus.h"

void	draw_cell_unit(t_cub3d *cub3d, int color, int x, int y)
{
	int	i;
	int	j;

	j = 0;
	while (j < CELL_UNIT)
	{
		i = 0;
		while (i < CELL_UNIT)
		{
			mlx_pixel_put(cub3d->mlx_ptr, cub3d->win, i + x, j + y, color);
			i++;
		}
		j++;
	}
}

void	draw_map_point(t_cub3d *cub3d, int x, int y)
{
	if (cub3d->map[y][x] == '1')
		draw_cell_unit(cub3d, 0x00FF0000, x * CELL_UNIT, y * CELL_UNIT);
	else if (cub3d->map[y][x] == '0')
		draw_cell_unit(cub3d, 0x0000FF00, x * CELL_UNIT, y * CELL_UNIT);
	else if (cub3d->map[y][x] == ' ')
		draw_cell_unit(cub3d, 0xFFFF000, x * CELL_UNIT, y * CELL_UNIT);
	else
		draw_cell_unit(cub3d, 0x00800080, x * CELL_UNIT, y * CELL_UNIT);
}

void	draw_map(t_cub3d *cub3d)
{
	int	i;
	int	j;

	i = 0;
	while (cub3d->map[i])
	{
		j = 0;
		while (cub3d->map[i][j])
		{
			draw_map_point(cub3d, j, i);
			j++;
		}
		i++;
	}
	draw_cell_unit(cub3d, 0x00800080, cub3d->player.pos.x * CELL_UNIT,
		cub3d->player.pos.y * CELL_UNIT);
}
