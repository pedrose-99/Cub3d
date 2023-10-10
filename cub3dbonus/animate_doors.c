/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate_doors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:54:14 by pfuentes          #+#    #+#             */
/*   Updated: 2023/10/04 13:54:31 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3dbonus.h"

void	move_door(t_cub3d *cub3d, t_list *doors, t_player *player)
{
	t_vector	next;
	t_door		*door;
	int			i;

	cub3d->keys[6] = 0;
	i = 0;
	while (i < 3)
	{
		next.x = player->pos.x + player->dir.x * i;
		next.y = player->pos.y + player->dir.y * i;
		door = find_door(doors, next.x, next.y);
		if (door)
		{
			cub3d->map[door->pos.y][door->pos.x] = 'D';
			if (door->move == 0)
				door->move = door->open;
			if (door->move < 0)
				door->move = 1;
			else if (door->move > 0)
				door->move = -1;
			animate_door(cub3d, door);
			return ;
		}
		i++;
	}
}

void	animate_door(t_cub3d *cub3d, t_door *door)
{
	door->border += 0.008 * door->move;
	if (door->border <= 0 || door->border >= 1)
	{
		door->open = door->move;
		door->move = 0;
	}
	if (door->border <= 0)
	{
		door->border = 0;
		cub3d->map[door->pos.y][door->pos.x] = '0';
	}
	else if (door->border > 1)
		door->border = 1;
}

void	animate_doors(t_cub3d *cub3d, t_list *doors)
{
	t_door		*door;

	while (doors)
	{
		door = (t_door *)doors->content;
		if (door->move != 0)
			animate_door(cub3d, door);
		doors = doors->next;
	}
}
