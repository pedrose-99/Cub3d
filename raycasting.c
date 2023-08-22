/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pserrano <pserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 10:27:59 by pserrano          #+#    #+#             */
/*   Updated: 2023/08/22 09:46:53 by pserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "minilibx_opengl_20191021/mlx.h"
#include "cub3d.h"
#include "libft/libft.h"

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
	draw_cell_unit(cub3d, 0x00800080, cub3d->player->pos.x * CELL_UNIT,
		cub3d->player->pos.y * CELL_UNIT);
}

double	degree_to_radians(double degree)
{
	return (degree * (M_PI / 180.0));
}

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
	rc.camera_scale = (2.0f * x / (double)WINDOW_X) - 1.0f;
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

static int	calculate_ray(t_raycaster *rc, char **map)
{
	double	distance;

	distance = 0;
	while (distance < RAY_MAX_DISTANCE) // bucle de ir generando el rayo y calcular paso a paso
	{
		if (rc->ray_len.x < rc->ray_len.y)
		{
			rc->map_pos.x += (int)rc->step_dir.x;
			distance = rc->ray_len.x;
			rc->ray_len.x += rc->step_incr.x;
			rc->side = 0;
		}
		else
		{
			rc->map_pos.y += (int)rc->step_dir.y;
			distance = rc->ray_len.y;
			rc->ray_len.y += rc->step_incr.y;
			rc->side = 1;
		}
		if ((rc->map_pos.x >= 0 && rc->map_pos.x < rc->map_len.x)
			&& (rc->map_pos.y >= 0 && rc->map_pos.y < rc->map_len.y))
		{
			if (map[rc->map_pos.y][rc->map_pos.x] == '1')
				return (1);
		}
		//printf("Distancia del rayo: %f\n", distance);
	}
	return (0);
}
static int	calculate_tex_x(t_img *texture, t_raycaster *rc)
{
	int		tex_x;
	double	wallx; //coordenada x o y exacta donde impactó el rayo

	tex_x = 0;
	if (rc->side == 0)
		wallx = rc->origin.y + rc->perp_wall_dist * rc->ray_dir.y;
	else
		wallx = rc->origin.x + rc->perp_wall_dist * rc->ray_dir.x;
	wallx -= floor((wallx));
	if ((rc->side == 0 && rc->ray_dir.x > 0)
		&& (rc->side == 1 && rc->ray_dir.y < 0))
		tex_x = texture->img_w - tex_x - 1;
	else
		tex_x = (int)(wallx * (double)(texture->img_w));
	return (tex_x);
}

static t_img	select_texture(t_cub3d *cub3d, t_player *player, t_raycaster *rc)
{
	t_img	texture;
	double	pos_diff_x;
	double	pos_diff_y;

	pos_diff_x = rc->map_pos.x - player->pos.x;
	pos_diff_y = rc->map_pos.y - player->pos.y;
	printf("Dir rayo: x %f, y %f\n", rc->ray_dir.x, rc->ray_dir.y);
	printf("Pos diff: x %f, y %f\n", pos_diff_x, pos_diff_y);
	texture = cub3d->textures[3]->img; // textura oeste
	if (rc->ray_dir.y < 0 && pos_diff_y < 0 && rc->side == 1) // textura sur
	{
		printf("Textura sur\n");
		texture = cub3d->textures[1]->img;
	}
	else if (rc->ray_dir.y > 0 && pos_diff_y > 0 && rc->side == 1) // textura norte
	{
		printf("Textura norte\n");
		texture = cub3d->textures[0]->img;
	}	
	else if (rc->ray_dir.x > 0 && pos_diff_x > 0 && rc->side == 0) // textura este
	{
		printf("Textura este\n");
		texture = cub3d->textures[2]->img;
	}
	else
		printf("Textura oeste\n");
	return (texture);
}

void	calculate_texture_pixel(t_cub3d *cub3d, t_raycaster *rc, int x)
{
	int		tex_x;
	int		tex_y;
	double	tex_pos;
	t_img	texture;
	double	step;
	int		y;

	texture = select_texture(cub3d, cub3d->player, rc);
	tex_x = calculate_tex_x(&texture, rc);
	step = 1.0 * texture.img_h / rc->line_height;
	tex_pos = (rc->draw_start - WINDOW_Y / 2 + rc->line_height / 2) * step;
	y = rc->draw_start;
	while (y < rc->draw_end)
	{
        tex_y = (int)tex_pos & (texture.img_h - 1);
        tex_pos += step;
       	cub3d->buffer.data[(y * WINDOW_X) + x]
			= texture.data[texture.img_h * tex_y + tex_x];
        if (rc->side == 1)
			cub3d->buffer.data[(y * WINDOW_X) + x]
					= (cub3d->buffer.data[(y * WINDOW_X) + x] >> 1) & 8355711;
		y++;
	}
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

t_img	new_img_rectangle(t_cub3d *cub3d, int width, int height, int color)
{
	int		x;
	int		y;
	t_img	img;

	img.img_ptr = mlx_new_image(cub3d->mlx_ptr, width, height);
	img.data = (int *)mlx_get_data_addr(img.img_ptr, &img.bpp, &img.size_l, &img.endian);
	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			img.data[(y * width) + x] = color;
			x++;
		}
		y++;
	}
	return (img);
}

void	waiting_events(t_cub3d *cub3d)
{
	mlx_hook(cub3d->win, 2, 1L<<0, &press_key, cub3d);
	mlx_hook(cub3d->win, 3, 1L<<1, &release_key, cub3d);
	mlx_hook(cub3d->win, 17, 0, close_window, cub3d);
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
