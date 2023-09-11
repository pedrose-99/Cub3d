/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 09:53:49 by pfuentes          #+#    #+#             */
/*   Updated: 2023/09/08 16:31:53 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	set_lim(floor(player->pos.x), &lim1.x, &lim2.x, ft_strlen(map[0]));
	set_lim(floor(player->pos.y), &lim1.y, &lim2.y, matrix_len(map));
	printf("Lim1: x %d, y %d\n", lim1.x, lim1.y);
	printf("Lim2: x %d, y %d\n", lim2.x, lim2.y);
	printf("Posición del jugador: x %f, y %f\n", player->pos.x, player->pos.y);
	i = 0;
	map[(int)player->pos.y][(int)player->pos.x] = 'P';
	while (lim1.y <= lim2.y)
	{
		minimap[i] = ft_substr(map[lim1.y], lim1.x, lim2.x - lim1.x + 1);
		printf("i: %d, lim1.y %d\n", i, lim1.y);
		i++;
		lim1.y++;
	}
	minimap[i] = NULL;
	print_matrix(minimap);
	map[(int)player->pos.y][(int)player->pos.x] = '0';
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

	buffer_pos.x = WINDOW_X - 250;
	buffer_pos.y = 30;
	minimap = new_minimap(cub3d->player, cub3d->map);
	printf("Minimapa creado\n");
	i = 0;
	while (minimap[i])
	{
		j = 0;
		while (minimap[i][j])
		{
			draw_minimap_point(cub3d->buffer.data,
				buffer_pos.y * WINDOW_X + buffer_pos.x, minimap[i][j]);
			buffer_pos.x += CELL_UNIT;
			j++;
		}
		buffer_pos.x = WINDOW_X - 250;
		buffer_pos.y += CELL_UNIT;
		i++;
	}
	printf("Liberar minimapa\n");
	free_matrix((void **)minimap);
}



