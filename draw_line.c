/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pserrano <pserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 09:53:06 by pfuentes          #+#    #+#             */
/*   Updated: 2023/08/22 12:05:03 by pserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//Meter en vectores
void	draw_line_dda(t_cub3d *cub3d, int x_start, int y_start, int x_end, int y_end)
{
	t_vector_d	delta;
	float		steps;
	t_vector_d	inc;
	t_vector_d	coor;
	int			i;

	delta.x = x_end - x_start;
	delta.y = y_end - y_start;
	if (fabs(delta.x) > fabs(delta.y))
		steps = fabs(delta.x);
	else
		steps = fabs(delta.y);
	inc.x = delta.x / steps;
	inc.y = delta.y / steps;
	coor.x = x_start;
	coor.y = y_start;
	i = 0;
	while (i < steps)
	{
		mlx_pixel_put(cub3d->mlx_ptr, cub3d->win, coor.x, coor.y, 0x00ffa500);
		coor.x += inc.x;
		coor.y += inc.y;
		i++;
	}
}
//No tocar
void	draw_line_bresenham(t_cub3d *cub3d, int x_start, int y_start, int x_end, int y_end)
{
	int	step_x;
	int	step_y;
	int	delta_x;
	int	delta_y;
	int	p;

	delta_x = x_end - x_start;
	delta_y = y_end - y_start;
	p = (2 * delta_x) - delta_y;
	if (delta_x < 0)
	{
		step_x = -1;
		delta_x *= -1;
	}
	else if (delta_x == 0)
		step_x = 0;
	else
		step_x = 1;
	if (delta_y < 0)
	{
		step_y = -1;
		delta_y *= -1;
	}
	else if (delta_y == 0)
		step_y = 0;
	else
		step_y = 1;
	//printf("x_start: %d, x_end: %d, y_start: %d, y_end: %d\n", x_start, x_end, y_start, y_end);
	if (abs(delta_x) > abs(delta_y))
	{
		while (x_start != x_end)
		{
			mlx_pixel_put(cub3d->mlx_ptr, cub3d->win, x_start, y_start, 0x00ffa500);
			x_start += step_x;
			if (p < 0)
				p += 2 * abs(delta_y);
			else
			{
				p += (2 * abs(delta_y)) - (2 * abs(delta_x));
				y_start += step_y;
			}
		}
	}
	else
	{
		//printf("delta y es mayor que delta x\n");
		while (y_start != y_end)
		{
			mlx_pixel_put(cub3d->mlx_ptr, cub3d->win, x_start, y_start, 0x00ffa500);
			y_start += step_y;
			if (p < 0)
				p += 2 * abs(delta_y);
			else
			{
				p += (2 * abs(delta_y)) - (2 * abs(delta_x));
				x_start += step_x;
			}
		}
	}
}
