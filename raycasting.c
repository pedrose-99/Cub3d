/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pserrano <pserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 10:27:59 by pserrano          #+#    #+#             */
/*   Updated: 2023/08/04 09:05:41 by pserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "minilibx_opengl_20191021/mlx.h"
#include "cub3d.h"
#include "libft/libft.h"

# define SQUARE 16
# define WINDOW_X 64
# define WINDOW_Y 64

void	draw_square(t_cub3d *cub3d, int color, int x, int y)
{
	int	i;
	int	j;

	j = 0;
	while (j < SQUARE)
	{
		i = 0;
		while (i < SQUARE)
		{
			mlx_pixel_put(cub3d->mlx_ptr, cub3d->win, i + x, j + y, color);
			i++;
		}
		j++;
	}
}
void	draw_map_point(t_cub3d *cub3d, int x, int y)
{
	printf("Casilla es: %c\n", cub3d->map[y][x]);
	if (cub3d->map[y][x] == '1')
		draw_square(cub3d, 0x00FF0000, x * SQUARE, y * SQUARE);
	else if (cub3d->map[y][x] == '0')
		draw_square(cub3d, 0x0000FF00, x * SQUARE, y * SQUARE);
	else if (cub3d->map[y][x] == ' ')
	{
		printf("Dibujar espacio\n");
		draw_square(cub3d, 0xFFFF000, x * SQUARE, y * SQUARE);
	}
	else
		draw_square(cub3d, 0x00800080, x * SQUARE, y * SQUARE);
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
	draw_square(cub3d, 0x00800080, cub3d->player.x * SQUARE,
		cub3d->player.y * SQUARE);
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
	draw_map_point(cub3d, cub3d->player.x, cub3d->player.y);
	reset_player_pos(&cub3d->player, cub3d->player.x + i, cub3d->player.y + j);
	draw_square(cub3d, 0x00800080, cub3d->player.x * SQUARE, cub3d->player.y * SQUARE);
}

void	draw_player_angle(t_cub3d *cub3d)
{
	int	y;
	int	cont;
	int	cont2;
	
	cont = 0;
	cont2 = 0;
	while (cont < 1)
	{
		cont2 = 0;
		printf("Tangente del ángulo: %f\n", tan(cub3d->player.angle));
		
		y = tan(cub3d->player.angle) * 
			(cub3d->player.x - cub3d->player.x + cont) + (y + cont);
		printf("x: %d, y: %d\n", cub3d->player.x - cont, y);
		while (cont2 < 10)
		{
			mlx_pixel_put(cub3d->mlx_ptr, cub3d->win,
				(cub3d->player.x + cont2) * SQUARE, y, 0x00800080);
			cont2 += 0.1;
		}
		cont += 0.1;
	}
}

void	set_player_angle(t_cub3d *cub3d, int add)
{
	printf("Set angle: %d\n", cub3d->player.angle);
	draw_player_angle(cub3d);
	cub3d->player.angle += add;
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
		set_player_angle(cub3d, -3);
	else if (key == 124)
		set_player_angle(cub3d, 3);
	else
		close_window(cub3d);
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
	/*if (map_is_close(normalized))
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
	cub3d->win = mlx_new_window(cub3d->mlx_ptr, screen_l, screen_h, "cub3d");
	//mlx_pixel_put(cub3d.mlx_ptr, cub3d.win, 200, 200, 0x0000FF00);
	search_player(cub3d, cub3d->map);
	draw_map(cub3d);
	printf("llega despues draw_map\n");
	waiting_events(cub3d);
	mlx_loop(cub3d->mlx_ptr);
}