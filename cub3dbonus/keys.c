/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 13:11:41 by pfuentes          #+#    #+#             */
/*   Updated: 2023/09/07 12:08:05 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

void	key_funcs(t_cub3d *cub3d)
{
	if (check_same_digit(cub3d->keys, 0, 7))
		return ;
	if (cub3d->keys[0] == 1)
		move_player_pos(cub3d, cub3d->player, 1, cub3d->player->dir);
	else if (cub3d->keys[1] == 1)
		move_player_pos(cub3d, cub3d->player, -1, cub3d->player->dir);
	else if (cub3d->keys[2] == 1)
		move_player_pos(cub3d, cub3d->player, -1, cub3d->player->plane);
	else if (cub3d->keys[3] == 1)
		move_player_pos(cub3d, cub3d->player, 1, cub3d->player->plane);
	if (cub3d->keys[4] == 1)
		move_player_angle(cub3d->player, -1);
	else if (cub3d->keys[5] == 1)
		move_player_angle(cub3d->player, 1);
	else if (cub3d->keys[6] == 1)
		move_door(cub3d, cub3d->doors, cub3d->player);
	//render_frame(cub3d);
}

int	press_key(int key, t_cub3d *cub3d)
{
	printf("Key: %d\n", key);
	if (key == MOVE_UP)
		cub3d->keys[0] = 1;
	else if (key == MOVE_DOWN)
		cub3d->keys[1] = 1;
	else if (key == MOVE_LEFT)
		cub3d->keys[2] = 1;
	else if (key == MOVE_RIGHT)
		cub3d->keys[3] = 1;
	if (key == ROT_LEFT)
		cub3d->keys[4] = 1;
	else if (key == ROT_RIGHT)
		cub3d->keys[5] = 1;
	else if (key == E_KEY)
		cub3d->keys[6] = 1;
	if (key == ESC)
		close_window(cub3d);
	return (0);
}
void	check_mouse_move(t_cub3d *cub3d, t_player *player)
{
	int	x;
	int	y;
	int	sign;

	sign = 1;
	mlx_mouse_get_pos(cub3d->win, &x, &y);
	sign = (x - (WINDOW_X / 2)) * 0.05;
	move_player_angle(player, sign);
	mlx_mouse_move(cub3d->win, WINDOW_X / 2, WINDOW_Y / 2);
}

int	release_key(int key, t_cub3d *cub3d)
{
	if (key == MOVE_UP)
		cub3d->keys[0] = 0;
	else if (key == MOVE_DOWN)
		cub3d->keys[1] = 0;
	else if (key == MOVE_LEFT)
		cub3d->keys[2] = 0;
	else if (key == MOVE_RIGHT)
		cub3d->keys[3] = 0;
	if (key == ROT_LEFT)
		cub3d->keys[4] = 0;
	else if (key == ROT_RIGHT)
		cub3d->keys[5] = 0;
	if (key == ESC)
		close_window(cub3d);
	return (0);
}

int	close_window(t_cub3d *cub3d)
{
	free_cub3d(cub3d, 0, 4);
	exit(0);
	return (0);
}

void	waiting_events(t_cub3d *cub3d)
{
	mlx_hook(cub3d->win, 2, 1L << 0, &press_key, cub3d);
	mlx_hook(cub3d->win, 3, 1L << 1, &release_key, cub3d);
	mlx_hook(cub3d->win, 17, 0, close_window, cub3d);
}
