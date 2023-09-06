/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 12:05:20 by pfuentes          #+#    #+#             */
/*   Updated: 2023/09/05 17:33:35 by pfuentes         ###   ########.fr       */
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
	door->open = 1;
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

void	animate_doors(t_cub3d *cub3d, t_list *doors)
{
	t_door	*door;

	while (doors)
	{
		door = (t_door *)doors->content;
		if (door->open == 1)
			door->border -= 0.01;
		if (door->border <= 0)
			door->open = 0;
		if (door->view == 1)
			render_frame(cub3d);
		doors = doors->next;
	}
}
