/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 09:53:49 by pfuentes          #+#    #+#             */
/*   Updated: 2023/09/07 11:55:16 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_vector	set_lim(t_player *player, int sign, char **map)
{
	t_vector	lim;
	int			i;

	i = 0;
	lim.x = player->pos.x;
	lim.y = player->pos.y;
	while (i <= 5)
	{
		lim.x += sign;
		lim.y += sign;
		i++;
	}
	if (sign == -1)
	{
		if (lim.x < 0)
			lim.x = 0;
		if (lim.y < 0)
			lim.y = 0;
	}
	else
	{
		if (lim.x > (int)ft_strlen(map[0]))
			lim.x = ft_strlen(map[0] - 1);
		if (lim.y > matrix_len(map))
			lim.y = matrix_len(map) - 1;
	}
	return (lim);
}

static char	**new_minimap(t_player *player, char **map)
{
	char		**minimap;
	int			i;
	t_vector	lim1;
	t_vector	lim2;

	minimap = (char **)malloc(sizeof(char *) * 12);
	lim1 = set_lim(player, -1, map);
	lim2 = set_lim(player, 1, map);
	printf("Lim1: x %d, y %d\n", lim1.x, lim1.y);
	printf("Lim2: x %d, y %d\n", lim2.x, lim2.y);
	printf("Posición del jugador: x %f, y %f\n", player->pos.x, player->pos.y);
	i = 0;
	while (lim1.y <= lim2.y)
	{
		minimap[i] = ft_substr(map[lim1.y], lim1.x, lim2.x - lim1.x);
		i++;
		lim1.y++;
	}
	minimap[i] = NULL;
	minimap[(int)player->pos.y][(int)player->pos.x] = 'P';
	return (minimap);
}

static void	draw_cell_unit(int *buffer, int pos, int color)
{
	int	i;
	int	j;

	j = 0;
	while (j < CELL_UNIT)
	{
		i = 0;
		while (i < CELL_UNIT)
		{
			buffer[pos + i] = color;
			//printf("Posición en buffer 'lineal': %d\n", pos + 1);
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
	else
		draw_cell_unit(buffer, pos, 0x00800080);
}

void	draw_minimap(t_cub3d *cub3d)
{
	char		**minimap;
	int			i;
	int			j;
	t_vector	buffer_pos;

	buffer_pos.x = 100;
	buffer_pos.y = 100;
	minimap = new_minimap(cub3d->player, cub3d->map);
	i = 0;
	while (minimap[i])
	{
		j = 0;
		while (minimap[i][j])
		{
			//printf("Posición en el buffer: x %d, y %d\n", buffer_pos.x, buffer_pos.y);
			draw_minimap_point(cub3d->buffer.data,
				buffer_pos.y * WINDOW_X + buffer_pos.x, minimap[i][j]);
			buffer_pos.x += CELL_UNIT;
			j++;
		}
		buffer_pos.x = 100;
		buffer_pos.y += CELL_UNIT;
		i++;
	}
	free_matrix((void **)minimap);
}



