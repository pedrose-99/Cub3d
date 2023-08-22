/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pserrano <pserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 10:27:59 by pserrano          #+#    #+#             */
/*   Updated: 2023/08/22 11:44:26 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "minilibx_opengl_20191021/mlx.h"
#include "cub3d.h"
#include "libft/libft.h"

double	degree_to_radians(double degree)
{
	return (degree * (M_PI / 180.0));
}

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

static t_raycaster	init_ray(t_cub3d *cub3d, int x)
{
	t_raycaster	rc;

	rc.origin.x = cub3d->player->pos.x;
	rc.origin.y = cub3d->player->pos.y;
	//printf("Origen del rayo: x %f, y %f\n", rc.origin.x, rc.origin.y);
	rc.map_pos.x = (int)rc.origin.x;
	rc.map_pos.y = (int)rc.origin.y;
	rc.camera_scale = 2.0f * x / (double)WINDOW_X - 1.0f;
	rc.ray_dir.x = cub3d->player->dir.x
		+ (cub3d->player->plane.x * cub3d->player->camera_plane)
		* rc.camera_scale;
	rc.ray_dir.y = cub3d->player->dir.y
		+ (cub3d->player->plane.y * cub3d->player->camera_plane)
		* rc.camera_scale;
	//printf("Raydir: x %f, y %f\n", rc.ray_dir.x, rc.ray_dir.y);
	if (rc.ray_dir.x == 0)
		rc.ray_dir.x = 1e30;
	if (rc.ray_dir.y == 0)
		rc.ray_dir.y = 1e30;
	rc.step_incr.x = fabs(1 / rc.ray_dir.x);
	rc.step_incr.y = fabs(1 / rc.ray_dir.y);
	//printf("Stepincr: x %f, y %f\n", rc.step_incr.x, rc.step_incr.y);
	rc.map_len.x = ft_strlen(cub3d->map[0]);
	rc.map_len.y = matrix_len(cub3d->map);
	init_ray_len_side(&rc);
	return (rc);
}

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
	//printf("Distancia del rayo: %f\n", rc->perp_wall_dist);
	rc->line_height = (int)(WINDOW_Y / rc->perp_wall_dist);
	rc->draw_start = -rc->line_height / 2 + WINDOW_Y / 2;
	if (rc->draw_start < 0)
		rc->draw_start = 0;
	rc->draw_end = rc->line_height / 2 + WINDOW_Y / 2;
	if (rc->draw_end >= WINDOW_Y)
		rc->draw_end = WINDOW_Y - 1;
	//draw_line_dda(cub3d, x, rc->draw_start, x, rc->draw_end);
}

void	cast_ray(t_cub3d *cub3d, int x)
{
	t_raycaster	ray;

	ray = init_ray(cub3d, x);
	//printf("Rayo inicializado\n");
	if (!calculate_ray(&ray, cub3d->map))
		return ;
	//printf("Rayo calculado\n");
	calculate_ray_line(&ray);
	//draw_line_dda(cub3d, x, ray.draw_start, x, ray.draw_end);
	//printf("Línea dibujada en base a rayo\n");
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
	mlx_put_image_to_window(cub3d->mlx_ptr, cub3d->win, cub3d->buffer.img_ptr, 0, 0);
}

int	main (void)
{
	t_cub3d *cub3d;
	char 	**map;
	int 	fd;

	cub3d = set_cub3d();
	fd = open("map2.ber", O_RDONLY);
	if (!set_visual_data(cub3d, fd))
	{
		printf("Invalid data format\n");
		return (1);
	}
	map = new_map(fd);
	char **normalized = normalize_map(map);
	free_matrix((void **)map);
	//print_map(normalized);
	if (map_is_close(normalized))
		print_matrix(normalized);
	else
	{
		printf("Mapa malo\n");
		return (1);
	}
	/*if (map_is_close(normalized))
	print_matrix(normalized);
	if (map_is_close(normalized))
		printf("Mapa bueno\n");
	else
		printf("Mapa malo\n");*/
	cub3d->map = normalized;
	cub3d->win = mlx_new_window(cub3d->mlx_ptr, WINDOW_X, WINDOW_Y, "cub3d");
	cub3d->player = set_player(cub3d->map);
	//draw_map(cub3d);
	waiting_events(cub3d);
	mlx_loop_hook(cub3d->mlx_ptr, &render_loop, cub3d);
	mlx_loop(cub3d->mlx_ptr);
}
