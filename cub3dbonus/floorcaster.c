/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floorcaster.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 11:45:44 by pfuentes          #+#    #+#             */
/*   Updated: 2023/10/06 11:18:02 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3dbonus.h"

static t_floorcaster	set_floorcaster(t_player *player, int y)
{
	t_floorcaster	fc;

	fc.ray_dir0.x = player->dir.x - player->plane.x;
	fc.ray_dir0.y = player->dir.y - player->plane.y;
	fc.ray_dir1.x = player->dir.x + player->plane.x;
	fc.ray_dir1.y = player->dir.y + player->plane.y;
	fc.p = y - (WINDOW_Y / 2);
	fc.pos_z = 0.5 * WINDOW_Y;
	fc.row_distance = fc.pos_z / fc.p;
	fc.floor_step.x = fc.row_distance * (fc.ray_dir1.x - fc.ray_dir0.x)
		/ WINDOW_X;
	fc.floor_step.y = fc.row_distance * (fc.ray_dir1.y - fc.ray_dir0.y)
		/ WINDOW_X;
	fc.floor_pos.x = player->pos.x + fc.row_distance * fc.ray_dir0.x;
	fc.floor_pos.y = player->pos.y + fc.row_distance * fc.ray_dir0.y;
	return (fc);
}	

static void	set_buffer_data(t_img *buffer, t_floorcaster *fc,
							t_img *img, int pos)
{
	int	tx;
	int	ty;
	int	color;

	tx = (int)(img->img_w * (fc->floor_pos.x - (int)(fc->floor_pos.x)))
		& (img->img_w - 1);
	ty = (int)(img->img_h * (fc->floor_pos.y - (int)(fc->floor_pos.y)))
		& (img->img_h - 1);
	color = (img->data[(ty * img->img_w) + tx]);
	buffer->data[pos] = color;
}

static void	set_floor_buffer(t_cub3d *cub3d, t_floorcaster *fc, int y, int x)
{
	set_buffer_data(&cub3d->buffer, fc, &cub3d->select_tex[5],
		(y * WINDOW_X) + x);
	set_buffer_data(&cub3d->buffer, fc, &cub3d->select_tex[4],
		((WINDOW_Y - y - 1) * WINDOW_X) + x);
	fc->floor_pos.x += fc->floor_step.x;
	fc->floor_pos.y += fc->floor_step.y;
}

void	floorcaster(t_cub3d *cub3d)
{
	int				y;
	t_floorcaster	fc;
	int				x;

	y = WINDOW_Y / 2;
	while (y < WINDOW_Y)
	{
		fc = set_floorcaster(&cub3d->player, y);
		x = 0;
		while (x < WINDOW_X)
		{
			set_floor_buffer(cub3d, &fc, y, x);
			x++;
		}
		y++;
	}
}
