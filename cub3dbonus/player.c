/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pserrano <pserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 10:50:51 by pfuentes          #+#    #+#             */
/*   Updated: 2023/09/06 10:26:40 by pserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_player_angle(t_player *player, char angle)
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

t_player	*set_player(char **map)
{
	t_player	*player;
	int			val;

	player = (t_player *)malloc(sizeof(t_player));
	val = init_player_pos(player, map);
	init_player_angle(player, val);
	player->dir.x = cos(degree_to_radians(player->angle));
	player->dir.y = -sin(degree_to_radians(player->angle));
	player->move_speed = 0.075;
	player->rot_speed = 0.04;
	player->camera_plane = tan(FOV / 2.0f * (M_PI / 180.0));
	player->plane.x = -player->dir.y * player->camera_plane;
	player->plane.y = player->dir.x * player->camera_plane;
	return (player);
}

void	move_player_pos_aux(t_player *player, int sign, t_vector_d mult, t_cub3d *cub3d)
{
	t_vector_d	pos_aux;
	int			x;
	int			y;

	pos_aux.x = player->pos.x + (mult.x * player->move_speed) * sign;
	pos_aux.y = player->pos.y + (mult.y * player->move_speed) * sign;
	x = floor(pos_aux.x);
	y = floor(pos_aux.y);
	if (cub3d->map[y][x] == '0')
	{
		player->pos.x += (mult.x * player->move_speed) * sign;
		player->pos.y += (mult.y * player->move_speed) * sign;
	}
	printf("Pos: x %f, y %f\n", player->pos.x, player->pos.y);
}

void	move_player_pos(t_player *player, int sign, t_vector_d mult)
{
	player->pos.x += (mult.x * player->move_speed) * sign;
	player->pos.y += (mult.y * player->move_speed) * sign;
	printf("Pos: x %f, y %f\n", player->pos.x, player->pos.y);
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
	/*player->angle += sign * 3;
	if (player->angle < 0)
		player->angle += 360;
	else if (player->angle > 360)
		player->angle -= 360;*/
	printf("Dir: x %f, y %f\n", player->dir.x, player->dir.y);
	printf("Plane: x %f, y %f\n", player->plane.x, player->plane.y);
}
