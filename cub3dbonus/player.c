/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 10:50:51 by pfuentes          #+#    #+#             */
/*   Updated: 2023/10/04 13:49:32 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3dbonus.h"

static int	init_player_pos(t_player *player, char **map)
{
	int		i;
	int		j;
	char	val;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' ||
				map[i][j] == 'W' || map[i][j] == 'E')
			{
				player->pos.x = j + 0.5;
				player->pos.y = i + 0.5;
				val = map[i][j];
				map[i][j] = '0';
				break ;
			}
			j++;
		}
		i++;
	}
	return (val);
}

void	set_player(t_player *player, char **map)
{
	int	val;

	val = init_player_pos(player, map);
	if (val == 'N')
		player->angle = N;
	else if (val == 'S')
		player->angle = S;
	else if (val == 'W')
		player->angle = W;
	else if (val == 'E')
		player->angle = E;
	player->dir.x = cos(degree_to_radians(player->angle));
	player->dir.y = -sin(degree_to_radians(player->angle));
	player->move_speed = 0.08;
	player->rot_speed = 0.04;
	player->camera_plane = tan(FOV / 2.0f * (M_PI / 180.0));
	player->plane.x = -player->dir.y * player->camera_plane;
	player->plane.y = player->dir.x * player->camera_plane;
}

void	move_player_pos(t_cub3d *cub3d, t_player *player,
						int sign, t_vector_d mult)
{
	t_vector_d	to_move;

	to_move.x = player->pos.x + (mult.x * player->move_speed) * sign;
	to_move.y = player->pos.y + (mult.y * player->move_speed) * sign;
	if (cub3d->map[(int)to_move.y][(int)to_move.x] == '0')
	{
		player->pos.x = to_move.x;
		player->pos.y = to_move.y;
	}
}

void	move_player_angle(t_player *player, int sign)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = player->dir.x;
	player->dir.x = player->dir.x * cos(sign * player->rot_speed)
		- player->dir.y * sin(sign * player->rot_speed);
	player->dir.y = old_dirx * sin(sign * player->rot_speed)
		+ player->dir.y * cos(sign * player->rot_speed);
	old_planex = player->plane.x;
	player->plane.x = player->plane.x * cos(sign * player->rot_speed)
		- player->plane.y * sin(sign * player->rot_speed);
	player->plane.y = old_planex * sin(sign * player->rot_speed)
		+ player->plane.y * cos(sign * player->rot_speed);
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
