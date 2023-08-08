/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_mal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 11:45:53 by pfuentes          #+#    #+#             */
/*   Updated: 2023/08/08 11:46:04 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "minilibx_opengl_20191021/mlx.h"
#include "cub3d.h"
#include "libft/libft.h"

# define CELL_UNIT 32
# define WINDOW_X 600
# define WINDOW_Y 400

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
	draw_cell_unit(cub3d, 0x00800080, cub3d->player->x * CELL_UNIT,
		cub3d->player->y * CELL_UNIT);
}
int	close_window(t_cub3d *cub3d)
{
	mlx_destroy_window(cub3d->mlx_ptr, cub3d->win);
	exit(0);
	return (0);
}

void	reset_player_pos(t_player *player, int x, int y)
{
	player->x = x;
	player->y = y;
}
void	player_movement(t_cub3d *cub3d, int i, int j)
{
	//draw_map_point(cub3d, cub3d->player->x, cub3d->player->y);
	reset_player_pos(cub3d->player, cub3d->player->x + i, cub3d->player->y + j);
	//draw_cell_unit(cub3d, 0x00800080, cub3d->player->x * CELL_UNIT, cub3d->player->y * CELL_UNIT);
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

void	set_plane(t_cub3d *cub3d)
{
	cub3d->raycaster->camera_plane = tan(FOV / 2.0f * (M_PI / 180.0));
	cub3d->raycaster->plane->x = - (cub3d->player->dir->y)
		* cub3d->raycaster->camera_plane;
	cub3d->raycaster->plane->y = cub3d->player->dir->x
		* cub3d->raycaster->camera_plane;
}

static void	set_ray_dir_y(t_cub3d *cub3d)
{
	if (cub3d->raycaster->ray_dir->y < 0)
	{
		cub3d->raycaster->step->y = 1;
		cub3d->raycaster->ray_length->y = (cub3d->player->pos->y
				- (float)cub3d->raycaster->map_check->y)
			* cub3d->raycaster->step_size->y;
	}
	else
	{
		cub3d->raycaster->step->y = -1;
		cub3d->raycaster->ray_length->y
			= ((float)(cub3d->raycaster->map_check->y + 1) - cub3d->player->pos->y)
			* cub3d->raycaster->step_size->y;
	}
}

static void	set_ray_dir_x(t_cub3d *cub3d)
{
	if (cub3d->raycaster->ray_dir->x < 0)
	{
		cub3d->raycaster->step->x = -1;
		cub3d->raycaster->ray_length->x = (cub3d->player->pos->x
				- (float)cub3d->raycaster->map_check->x)
			* cub3d->raycaster->step_size->x;
	}
	else
	{
		cub3d->raycaster->step->x = 1;
		cub3d->raycaster->ray_length->x
			= ((float)(cub3d->raycaster->map_check->x + 1) - cub3d->player->pos->x)
			* cub3d->raycaster->step_size->x;
	}
}

void	set_ray(t_cub3d *cub3d, int x)
{
	cub3d->raycaster->map_check->x = cub3d->player->pos->x;
	cub3d->raycaster->map_check->y = cub3d->player->pos->y;
	cub3d->raycaster->camera_scale = (2.0f * x / WINDOW_X) - 1.0f;
	cub3d->raycaster->ray_dir->x = (cub3d->player->dir->x
		+ cub3d->raycaster->plane->x) * cub3d->raycaster->camera_scale;
	cub3d->raycaster->ray_dir->y = (cub3d->player->dir->y
		+ cub3d->raycaster->plane->y) * cub3d->raycaster->camera_scale;
	cub3d->raycaster->step_size->x = fabs(1 / cub3d->raycaster->ray_dir->x);
	cub3d->raycaster->step_size->y = fabs(1 / cub3d->raycaster->ray_dir->y);
	set_ray_dir_x(cub3d);
	set_ray_dir_y(cub3d);
}

void	draw_ray_line(t_cub3d *cub3d, int x)
{
	int	line_height;
	int	draw_start;
	int	draw_end;

	printf("%f %f\n", cub3d->raycaster->ray_length->x, cub3d->raycaster->step_size->x);
	printf("%f %f\n", cub3d->raycaster->ray_length->y, cub3d->raycaster->step_size->y);
	if (cub3d->raycaster->side == 0)
		cub3d->raycaster->perp_wall_dist = cub3d->raycaster->ray_length->x
			- cub3d->raycaster->step_size->x;
	else
		cub3d->raycaster->perp_wall_dist = cub3d->raycaster->ray_length->y
			- cub3d->raycaster->step_size->y;
	printf("Perp wall: %f\n", cub3d->raycaster->perp_wall_dist);
	line_height = (int)(WINDOW_Y / cub3d->raycaster->perp_wall_dist);
	draw_start = -line_height / 2 + WINDOW_Y / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + WINDOW_Y / 2;
	if (draw_end >= WINDOW_Y)
		draw_end = WINDOW_Y - 1;
	printf("Dibujar línea: x %d, y start %d, y end %d\n\n", x, draw_start, draw_end);
	draw_line_dda(cub3d, x, draw_start, x, draw_end);
	printf("Línea dibujada\n");
}

int	check_ray_collision(t_cub3d *cub3d)
{
	int	collision;
	int	map_lenx;
	int	map_leny;

	collision = 0;
	map_lenx = ft_strlen(cub3d->map[0]);
	map_leny = matrix_len(cub3d->map);
	while (collision == 0)
	{
		if (cub3d->raycaster->ray_length->x < cub3d->raycaster->ray_length->y)
		{
			cub3d->raycaster->map_check->x += cub3d->raycaster->step->x;
			cub3d->raycaster->ray_length->x += cub3d->raycaster->step_size->x;
			cub3d->raycaster->side = 0;
		}
		else
		{
			cub3d->raycaster->map_check->y += cub3d->raycaster->step->y;
			cub3d->raycaster->ray_length->y += cub3d->raycaster->step_size->y;
			cub3d->raycaster->side = 1;
		}
		if ((cub3d->raycaster->map_check->x >= 0
				&& cub3d->raycaster->map_check->x < map_lenx)
			&& (cub3d->raycaster->map_check->y >= 0
				&& cub3d->raycaster->map_check->y < map_leny))
		{
			if (cub3d->map[cub3d->raycaster->map_check->y]
				[cub3d->raycaster->map_check->x] == '1')
				collision = 1;
		}
	}
	return (1);
}

void	cast_ray(t_cub3d *cub3d)
{
	int	x;

	x = 0;
	printf("Cast_ray\n");
	while (x < WINDOW_X)
	{
		set_ray(cub3d, x);
		printf("Rayo seteado\n");
		if (check_ray_collision(cub3d) == 1)
		{
			printf("Dibujar rayo\n");
			draw_ray_line(cub3d, x);
		}
		printf("Rayo %d casteado\n", x);
		//printf("Punto de colisión: '%c', x %d, y %d\n", cub3d->map[mapchecky][mapcheckx],
		//		mapcheckx, mapchecky);
		//draw_line_dda(cub3d, playerx * CELL_UNIT, playery * CELL_UNIT,
		//	(mapcheckx + 0->5) * CELL_UNIT, mapchecky * CELL_UNIT);
		//draw_cell_unit(cub3d, 0x00ffa500, mapcheckx * CELL_UNIT, mapchecky * CELL_UNIT);
		//printf("coordenada x: %d\n", x);
		x++;
	}
	printf("Casteó todos los rayos\n");
}

void	set_player_angle(t_cub3d *cub3d, int add)
{
	//draw_map(cub3d);
	//printf("Set angle: %d\n", cub3d->player->angle);
	cub3d->player->angle += add;
	if (cub3d->player->angle >= 360)
		cub3d->player->angle -= 360;
	else if (cub3d->player->angle <= 0)
		cub3d->player->angle += 360;
}

int	key_hook(int key, t_cub3d *cub3d)
{
	printf("Key: %d\n", key);
	if (key == 53)
		close_window(cub3d);
	if (key == 13)
		player_movement(cub3d, 0, -1);
	else if (key == 0)
		player_movement(cub3d, -1, 0);
	else if (key == 1)
		player_movement(cub3d, 0, 1);
	else if (key == 2)
		player_movement(cub3d, 1, 0);
	else if (key == 123)
		set_player_angle(cub3d, 10);
	else if (key == 124)
		set_player_angle(cub3d, -10);
	else
		close_window(cub3d);
	cast_ray(cub3d);
	return (0);
}

void	waiting_events(t_cub3d *cub3d)
{
	mlx_key_hook(cub3d->win, *key_hook, cub3d);
	mlx_hook(cub3d->win, 17, 0, close_window, cub3d);
}

void	init_player_angle(t_player *player, char angle)
{
	if (angle == 'N')
		player->angle = N;
	else if (angle == 'S')
		player->angle = S;
	else if (angle == 'W')
		player->angle = W;
	else if (angle == 'E')
		player->angle = E;
}

void	set_player(t_player	*player, char **map)
{
	int	i;
	int	j;

	i = 0;
	player->pos = (t_vectord *)malloc(sizeof(t_vectord));
	player->dir = (t_vectord *)malloc(sizeof(t_vectord));
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' ||
				map[i][j] == 'W' || map[i][j] == 'E')
			{
				player->pos->x = j + 0.5;
				player->pos->y = i + 0.5;
				player->dir->x = cos(degree_to_radians(player->angle));
				player->dir->y = sin(degree_to_radians(player->angle));
				init_player_angle(player, map[i][j]);
				map[i][j] = '0';
				break ;
			}
			j++;
		}
		i++;
	}
}

void	set_raycaster(t_raycaster *raycaster)
{
	raycaster->plane = (t_vectord *)malloc(sizeof(t_vectord));
	raycaster->ray_length = (t_vectord *)malloc(sizeof(t_vectord));
	raycaster->step = (t_vectord *)malloc(sizeof(t_vectord));
	raycaster->map_check = (t_vector *)malloc(sizeof(t_vector));
	raycaster->ray_dir = (t_vectord *)malloc(sizeof(t_vectord));
	raycaster->step_size = (t_vectord *)malloc(sizeof(t_vectord));
}

int	main (void)
{
	int	screen_l;
	int	screen_h;
	t_cub3d *cub3d;
	char **map;
	int fd;
	int	size_y = 0;
	int size_x;

	cub3d = (t_cub3d *)malloc(sizeof(t_cub3d));
	fd = open("mapprueba.ber", O_RDONLY);
	map = new_map(fd);
	char **normalized = normalize_map(map);
	//print_map(normalized);
	if (map_is_close(normalized))
		print_matrix(normalized);
	/*if (map_is_close(normalized))
	print_matrix(normalized);
	if (map_is_close(normalized))
		printf("Mapa bueno\n");
	else
		printf("Mapa malo\n");*/
	size_x = (int)ft_strlen(map[0]);
	while (map[size_y])
		size_y++;
	screen_h = WINDOW_Y * size_y;
	screen_l = WINDOW_X * size_x;
	cub3d->map = normalized;
	cub3d->mlx_ptr = mlx_init();
	cub3d->win = mlx_new_window(cub3d->mlx_ptr, WINDOW_X, WINDOW_Y, "cub3d");
	printf("Creó cub3d y mlx\n");
	//mlx_pixel_put(cub3d->mlx_ptr, cub3d->win, 200, 200, 0x0000FF00);
	cub3d->player = (t_player *)malloc(sizeof(t_player));
	cub3d->raycaster = (t_raycaster *)malloc(sizeof(t_raycaster));
	set_player(cub3d->player, cub3d->map);
	set_raycaster(cub3d->raycaster);
	waiting_events(cub3d);
	printf("Castear rayos\n");
	cast_ray(cub3d);
	//draw_map(cub3d);
	
	mlx_loop(cub3d->mlx_ptr);
}