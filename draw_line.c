/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 09:53:06 by pfuentes          #+#    #+#             */
/*   Updated: 2023/08/22 09:53:15 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_line_dda(t_cub3d *cub3d, int x_start, int y_start, int x_end, int y_end)
{
	float	delta_x;
	float	delta_y;
	float	steps;
	float 	x_inc;
	float	y_inc;
	float	x;
	float	y;

	//printf("x_start: %d, x_end: %d, y_start: %d, y_end: %d\n", x_start, x_end, y_start, y_end);
	delta_x = x_end - x_start;
	delta_y = y_end - y_start;
	if (fabs(delta_x) > fabs(delta_y))
		steps = fabs(delta_x);
	else
		steps = fabs(delta_y);
	//printf("Delta_x: %f, steps: %f\n", delta_x, steps);
	x_inc = delta_x / steps;
	y_inc = delta_y / steps;
	x = x_start;
	y = y_start;
	//printf("xinc: %f, yinc: %f\n", x_inc, y_inc);
	int	i = 0;
	while (i < steps)
	{
		mlx_pixel_put(cub3d->mlx_ptr, cub3d->win, x, y, 0x00ffa500);
		//printf("x: %d, y: %d\n", x_start, y_start);
		x += x_inc;
		y += y_inc;
		i++;
	}
}

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