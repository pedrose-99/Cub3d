/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_raycast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:37:25 by pserrano          #+#    #+#             */
/*   Updated: 2023/10/04 11:21:56 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_ray_len_side(t_raycaster *rc)
{
	if (rc->ray_dir.x < 0)
	{
		rc->step_dir.x = -1;
		rc->ray_len.x = (rc->origin.x
				- (double)rc->map_pos.x) * rc->step_incr.x;
	}
	else
	{
		rc->step_dir.x = 1;
		rc->ray_len.x = ((double)(rc->map_pos.x + 1.0)
				- rc->origin.x) * rc->step_incr.x;
	}
	if (rc->ray_dir.y < 0)
	{
		rc->step_dir.y = -1;
		rc->ray_len.y = (rc->origin.y
				- (double)rc->map_pos.y) * rc->step_incr.y;
	}
	else
	{
		rc->step_dir.y = 1;
		rc->ray_len.y = ((double)(rc->map_pos.y + 1.0)
				- rc->origin.y) * rc->step_incr.y;
	}
}

t_raycaster	init_ray(t_cub3d *cub3d, int x)
{
	t_raycaster	rc;

	rc.origin.x = cub3d->player.pos.x;
	rc.origin.y = cub3d->player.pos.y;
	rc.map_pos.x = (int)rc.origin.x;
	rc.map_pos.y = (int)rc.origin.y;
	rc.camera_scale = 2.0f * x / (double)WINDOW_X - 1.0f;
	rc.ray_dir.x = cub3d->player.dir.x
		+ (cub3d->player.plane.x * cub3d->player.camera_plane)
		* rc.camera_scale;
	rc.ray_dir.y = cub3d->player.dir.y
		+ (cub3d->player.plane.y * cub3d->player.camera_plane)
		* rc.camera_scale;
	if (rc.ray_dir.x == 0)
		rc.ray_dir.x = 1e30;
	if (rc.ray_dir.y == 0)
		rc.ray_dir.y = 1e30;
	rc.step_incr.x = fabs(1 / rc.ray_dir.x);
	rc.step_incr.y = fabs(1 / rc.ray_dir.y);
	rc.map_len.x = ft_strlen(cub3d->map[0]);
	rc.map_len.y = matrix_len(cub3d->map);
	init_ray_len_side(&rc);
	return (rc);
}
