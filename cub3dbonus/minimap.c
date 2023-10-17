/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 09:53:49 by pfuentes          #+#    #+#             */
/*   Updated: 2023/10/16 12:07:51 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3dbonus.h"

static void	set_lim(int player, int *lim1, int *lim2, int max)
{
	*lim1 = player - 5;
	*lim2 = player + 5;
	if (*lim1 < 0)
	{
		*lim2 += 5 - player;
		*lim1 = 0;
	}
	if (*lim2 > max)
	{
		*lim1 -= *lim2 - max;
		*lim2 = player + (max - player);
	}
}

static char	**new_minimap(t_player *player, char **map)
{
	char		**minimap;
	int			i;
	t_vector	lim1;
	t_vector	lim2;

	minimap = (char **)malloc(sizeof(char *) * 12);
	set_lim(floor(player->pos.x), &lim1.x, &lim2.x, ft_strlen(map[0]) - 1);
	set_lim(floor(player->pos.y), &lim1.y, &lim2.y, matrix_len(map) - 1);
	i = 0;
	map[(int)player->pos.y][(int)player->pos.x] = 'P';
	while (lim1.y <= lim2.y)
	{
		minimap[i] = ft_substr(map[lim1.y], lim1.x, lim2.x - lim1.x + 1);
		i++;
		lim1.y++;
	}
	minimap[i] = NULL;
	map[(int)player->pos.y][(int)player->pos.x] = '0';
	return (minimap);
}

static void	draw_cell_unit(int *buffer, int pos, int color)
{
	int	i;
	int	j;

	j = 0;
	while (j < WINDOW_X / 80)
	{
		i = 0;
		while (i < WINDOW_X / 80)
		{
			buffer[pos + i] = color;
			i++;
		}
		pos += WINDOW_X;
		j++;
	}
}

static void	draw_minimap_point(int *buffer, int pos, char symbol)
{
	if (symbol == '1')
		draw_cell_unit(buffer, pos, 0x00FF0000);
	else if (symbol == '0')
		draw_cell_unit(buffer, pos, 0x0000FF00);
	else if (symbol == ' ')
		draw_cell_unit(buffer, pos, 0xFFFF000);
	else if (symbol == 'P')
		draw_cell_unit(buffer, pos, 0x00800080);
	else if (symbol == 'D')
		draw_cell_unit(buffer, pos, 0x00228B22);
}

void	draw_minimap(t_cub3d *cub3d)
{
	char		**minimap;
	int			i;
	int			j;
	t_vector	buffer_pos;

	buffer_pos.x = 5 * (WINDOW_X / 6);
	buffer_pos.y = WINDOW_Y / 20;
	minimap = new_minimap(&cub3d->player, cub3d->map);
	i = 0;
	while (minimap[i])
	{
		j = 0;
		while (minimap[i][j])
		{
			draw_minimap_point(cub3d->buffer.data,
				buffer_pos.y * WINDOW_X + buffer_pos.x, minimap[i][j]);
			buffer_pos.x += WINDOW_X / 80;
			j++;
		}
		buffer_pos.x = 5 * (WINDOW_X / 6);
		buffer_pos.y += WINDOW_X / 80;
		i++;
	}
	free_matrix((void **)minimap);
}
