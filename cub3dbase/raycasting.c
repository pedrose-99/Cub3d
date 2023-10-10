/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 10:27:59 by pserrano          #+#    #+#             */
/*   Updated: 2023/10/04 11:21:12 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ray_inside_cell(t_raycaster *rc, char **map)
{
	if ((rc->map_pos.x >= 0 && rc->map_pos.x < rc->map_len.x)
		&& (rc->map_pos.y >= 0 && rc->map_pos.y < rc->map_len.y))
	{
		if (map[rc->map_pos.y][rc->map_pos.x] == '1')
			return (1);
	}
	return (0);
}

static int	calculate_ray(t_raycaster *rc, char **map)
{
	double	distance;

	distance = 0;
	while (distance < RAY_MAX_DISTANCE)
	{
		if (rc->ray_len.x < rc->ray_len.y)
		{
			rc->map_pos.x += rc->step_dir.x;
			distance = rc->ray_len.x;
			rc->ray_len.x += rc->step_incr.x;
			rc->side = 0;
		}
		else
		{
			rc->map_pos.y += rc->step_dir.y;
			distance = rc->ray_len.y;
			rc->ray_len.y += rc->step_incr.y;
			rc->side = 1;
		}
		if (ray_inside_cell(rc, map))
			return (1);
	}
	return (0);
}

static void	calculate_ray_line(t_raycaster *rc)
{
	if (rc->side == 0)
		rc->perp_wall_dist = rc->ray_len.x - rc->step_incr.x;
	else
		rc->perp_wall_dist = rc->ray_len.y - rc->step_incr.y;
	rc->line_height = (int)(WINDOW_Y / rc->perp_wall_dist);
	rc->draw_start = -rc->line_height / 2 + WINDOW_Y / 2;
	if (rc->draw_start < 0)
		rc->draw_start = 0;
	rc->draw_end = rc->line_height / 2 + WINDOW_Y / 2;
	if (rc->draw_end >= WINDOW_Y)
		rc->draw_end = WINDOW_Y - 1;
}

void	cast_ray(t_cub3d *cub3d, int x)
{
	t_raycaster	ray;

	ray = init_ray(cub3d, x);
	if (!calculate_ray(&ray, cub3d->map))
		return ;
	calculate_ray_line(&ray);
	calculate_texture_pixel(cub3d, &ray, x);
}

void	raycaster(t_cub3d *cub3d)
{
	int			x;

	x = 0;
	while (x < WINDOW_X)
	{
		cast_ray(cub3d, x);
		x++;
	}
	mlx_put_image_to_window(cub3d->mlx_ptr, cub3d->win,
		cub3d->buffer.img_ptr, 0, 0);
}
