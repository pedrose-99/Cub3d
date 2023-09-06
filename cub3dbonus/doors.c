/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 12:05:20 by pfuentes          #+#    #+#             */
/*   Updated: 2023/09/06 13:00:28 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_door	*find_door(t_list *doors, int x, int y)
{
	t_door	*door;

	while (doors)
	{
		door = (t_door *)doors->content;
		if (door->pos.x == x && door->pos.y == y)
			return (door);
		doors = doors->next;
	}
	return (NULL);
}

t_door	*new_door(int x, int y)
{
	t_door	*door;

	door = (t_door *)malloc(sizeof(t_door));
	door->pos.x = x;
	door->pos.y = y;
	door->move = 0;
	door->open = -1;
	door->view = 0;
	door->border = 1;
	return (door);
}

t_list	*set_doors_lst(char **map)
{
	t_list	*doors;
	int		i;
	int		j;

	doors = NULL;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'D')
				ft_lstadd_back(&doors, ft_lstnew((void *)new_door(j, i)));
			j++;
		}
		i++;
	}
	return (doors);
}

void	move_door(t_cub3d *cub3d, t_list *doors, t_player *player)
{
	t_vector	next;
	t_door		*door;

	cub3d->keys[6] = 0;
	next.x = player->pos.x + player->dir.x;
	next.y = player->pos.y + player->dir.y;
	door = find_door(doors, next.x, next.y);
	if (!door)
		return ;
	cub3d->map[door->pos.y][door->pos.x] = 'D';
	if (door->move == 0)
		door->move = door->open;
	if (door->move < 0)
		door->move = 1;
	else if (door->move > 0)
		door->move = -1;
	animate_door(cub3d, door);
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
	if (door->view == 1)
		render_frame(cub3d);
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
