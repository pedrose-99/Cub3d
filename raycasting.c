/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 10:27:59 by pserrano          #+#    #+#             */
/*   Updated: 2023/08/08 16:25:55 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "minilibx_opengl_20191021/mlx.h"
#include "cub3d.h"
#include "libft/libft.h"

# define CELL_UNIT 32
# define WINDOW_X 1280
# define WINDOW_Y 720

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
	draw_cell_unit(cub3d, 0x00800080, cub3d->player.x * CELL_UNIT,
		cub3d->player.y * CELL_UNIT);
}
int	close_window(t_cub3d *cub3d)
{
	mlx_destroy_window(cub3d->mlx_ptr, cub3d->win);
	exit(0);
	return (0);
}

double	degree_to_radians(double degree)
{
	return (degree * (M_PI / 180.0));
}

void	draw_line_dda(t_cub3d *cub3d, int x_start, int y_start, int x_end, int y_end)
{
	float	delta_x;
	float	delta_y;
	float		steps;
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

void	cast_ray(t_cub3d *cub3d)
{
	double		playerx = cub3d->player.x + 0.5; //posicion del jugador
	double		playery = cub3d->player.y + 0.5;
	double	dirx = cub3d->dirx;
	double	diry = cub3d->diry;
	//printf("Vector director: %f, %f\n", dirx, diry);
	//double	rightx = -diry;
	//double	righty = dirx;
	//double	camPlane = tan( FOV / 2.0f * (M_PI / 180.0) );

	double 	planex = cub3d->planex;
	double	planey = cub3d->planey; 
	double	raylengthx; //guarda longitud del rayo en filas y columnas "acumuladas"
	double	raylengthy;

	double	stepx; //direccion en eje x e y
	double	stepy;

	int	x = 0;
	while (x < WINDOW_X)
	{
		int		mapcheckx = (int)playerx; //posicion en el mapa
		int		mapchecky = (int)playery;
		double cameraScale = (2.0f * x / WINDOW_X) - 1.0f; //x-coordinate in camera space
		//printf("cameraScale: %f\n", cameraScale);
     	double rayDirX = dirx + planex * cameraScale;
      	double rayDirY = diry + planey * cameraScale;
		double	stepsizex = fabs(1 / rayDirX); // delta o incrementos en cada paso
		double	stepsizey = fabs(1 / rayDirY);
		double 	perpWallDist; //perp = distancia perpendicular al muro

      	int side; //was a NS or a EW wall hit?
		if (rayDirX < 0)
		{
			stepx = -1;
			raylengthx = (playerx - (float)mapcheckx) * stepsizex;
		}
		else
		{
			stepx = 1;
			raylengthx = ((float)(mapcheckx + 1.0) - playerx) * stepsizex;
		}
		if (rayDirY < 0)
		{
			stepy = -1;
			raylengthy = (playery - (float)mapchecky) * stepsizey;
		}
		else
		{
			stepy = 1;
			raylengthy = ((float)(mapchecky + 1.0) - playery) * stepsizey;
		}
		
		int	map_lenx = ft_strlen(cub3d->map[0]);
		int	map_leny = matrix_len(cub3d->map);
		int	collision = 0;
		while (collision == 0)
		{
			if (raylengthx < raylengthy)
			{
				mapcheckx += stepx;
				raylengthx += stepsizex;
				side = 0;
			}
			else
			{
				mapchecky += stepy;
				raylengthy += stepsizey;
				side = 1;
			}
			if ((mapcheckx >= 0 && mapcheckx < map_lenx)
				&& (mapchecky >= 0 && mapchecky < map_leny))
			{
				if (cub3d->map[mapchecky][mapcheckx] == '1')
					collision = 1;
			}
		}
		//printf("Punto de colisión: '%c', x %d, y %d\n", cub3d->map[mapchecky][mapcheckx],
		//		mapcheckx, mapchecky);
		//draw_line_dda(cub3d, playerx * CELL_UNIT, playery * CELL_UNIT,
			//(mapcheckx + 0.5) * CELL_UNIT, mapchecky * CELL_UNIT);
		//draw_cell_unit(cub3d, 0x00ffa500, mapcheckx * CELL_UNIT, mapchecky * CELL_UNIT);
		//printf("coordenada x: %d\n", x);
		if (side == 0)
			perpWallDist = raylengthx - stepsizex;
		else
			perpWallDist = raylengthy - stepsizey;
		int	lineHeight = (int)( WINDOW_Y / perpWallDist);
		int drawStart = -lineHeight / 2 + WINDOW_Y / 2;
     	if (drawStart < 0)
			drawStart = 0;
     	int drawEnd = lineHeight / 2 + WINDOW_Y / 2;
      	if (drawEnd >= WINDOW_Y)
			drawEnd = WINDOW_Y - 1;
		draw_line_dda(cub3d, x, drawStart, x, drawEnd);
		x++;
	}
}

void	move_angle(t_cub3d *cub3d, int sign)
{
	double oldDirX = cub3d->dirx;
    cub3d->dirx = cub3d->dirx * cos(sign * cub3d->rot_speed) - cub3d->diry * sin(sign * cub3d->rot_speed);
    cub3d->diry = oldDirX * sin(sign * cub3d->rot_speed) + cub3d->diry * cos(sign * cub3d->rot_speed);
    double oldPlaneX = cub3d->planex;
    cub3d->planex = cub3d->planex * cos(sign * cub3d->rot_speed) - cub3d->planey * sin(sign * cub3d->rot_speed);
    cub3d->planey = oldPlaneX * sin(sign * cub3d->rot_speed) + cub3d->planey * cos(sign * cub3d->rot_speed);
}

void	player_movement_y(t_cub3d *cub3d, int sign)
{
	//draw_map_point(cub3d, cub3d->player.x, cub3d->player.y);
	printf("Vector director: x %f, y %f\n", cub3d->dirx, cub3d->diry);
	printf("Player: x %f, y %f\n", cub3d->player.x, cub3d->player.y);
	if (sign == 1)
	{
		cub3d->player.x += cub3d->dirx * cub3d->move_speed;
		printf("Suma a x: %f\n", cub3d->dirx * cub3d->move_speed);
		cub3d->player.y += cub3d->diry * cub3d->move_speed;
		printf("Suma a y: %f\n", cub3d->diry * cub3d->move_speed);
	}
	else
	{
		cub3d->player.x -= cub3d->dirx * cub3d->move_speed;
		cub3d->player.y -= cub3d->diry * cub3d->move_speed;
	}
	//cub3d->player.x += i;
	//cub3d->player.y += j;
	printf("Player: x %f, y %f\n", cub3d->player.x, cub3d->player.y);
	//draw_cell_unit(cub3d, 0x00800080, cub3d->player.x * CELL_UNIT, cub3d->player.y * CELL_UNIT);
}

void	player_movement_x(t_cub3d *cub3d, int sign)
{
	float	aux_x;
	float	aux_y;

	if (sign == 1)
	{
		printf("el dir x es %f, dir y es %f\n", cub3d->dirx, cub3d->diry);
		printf("el ang x es %f, ang y es %f\n", acosf(cub3d->dirx), asinf(cub3d->diry));
		aux_x = acosf(cub3d->dirx) - (M_PI / 2);
		aux_x = cosf(aux_x);
		aux_y = asinf(cub3d->diry) - (M_PI / 2);
		aux_y = sinf(aux_y);
		printf("Auxy es %f, auxx es %f\n", aux_y, aux_x);
		cub3d->player.x -= aux_x * cub3d->move_speed;
		cub3d->player.y -= aux_y * cub3d->move_speed;
	//	printf("Auuxy es %f, auxx es %f\n", aux_y, aux_x);
	}
	else
	{
		aux_x = acosf(cub3d->dirx) + (M_PI / 2);
		aux_x = cosf(aux_x);
		aux_y = asinf(cub3d->diry) + (M_PI / 2);
		aux_y = sinf(aux_y);
		cub3d->player.x += aux_x * cub3d->move_speed;
		cub3d->player.y += aux_y * cub3d->move_speed;
	}
	printf("Posición del jugador: x %f, y %f\n", cub3d->player.x, cub3d->player.y);
}

int	key_hook(int key, t_cub3d *cub3d)
{
	printf("Key: %d\n", key);
	if (key == ESC)
		close_window(cub3d);
	if (key == MOVE_UP)
		player_movement_y(cub3d, 1);
	else if (key == MOVE_DOWN)
		player_movement_y(cub3d, -1);
	else if (key == MOVE_LEFT)
		player_movement_x(cub3d, -1);
	else if (key == MOVE_RIGHT)
		player_movement_x(cub3d, 1);
	else if (key == ROT_LEFT)
		move_angle(cub3d, -1);
	else if (key == ROT_RIGHT)
		move_angle(cub3d, 1);
	else
		close_window(cub3d);
	mlx_clear_window(cub3d->mlx_ptr, cub3d->win);
	//draw_map(cub3d);
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

void	search_player(t_cub3d *cub3d, char **map)
{
	int i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' ||
				map[i][j] == 'W' || map[i][j] == 'E')
			{
				cub3d->player.x = j;
				cub3d->player.y = i;
				init_player_angle(&cub3d->player, map[i][j]);
				map[i][j] = '0';
				break ;
			}
			j++;
		}
		i++;
	}
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
	cub3d->dirx = cos(degree_to_radians(cub3d->player.angle)); // vector director
	cub3d->diry = sin(degree_to_radians(cub3d->player.angle));
	cub3d->move_speed =  0.2; //the constant value is in squares/second
    cub3d->rot_speed = 0.1;
	double	camPlane = tan( FOV / 2.0f * (M_PI / 180.0) );
	cub3d->planex = -cub3d->diry * camPlane;
	cub3d->planey = cub3d->dirx * camPlane;
	//mlx_pixel_put(cub3d.mlx_ptr, cub3d.win, 200, 200, 0x0000FF00);
	search_player(cub3d, cub3d->map);
	draw_map(cub3d);
	waiting_events(cub3d);
	mlx_loop(cub3d->mlx_ptr);
}