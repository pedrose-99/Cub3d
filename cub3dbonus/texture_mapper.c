/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_mapper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 12:58:03 by pserrano          #+#    #+#             */
/*   Updated: 2023/10/04 13:52:01 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3dbonus.h"

void	calculate_wall_x(t_raycaster *rc)
{
	double	wallx;

	if (rc->side == 0)
		wallx = rc->origin.y + rc->perp_wall_dist * rc->ray_dir.y;
	else
		wallx = rc->origin.x + rc->perp_wall_dist * rc->ray_dir.x;
	wallx -= floor((wallx));
	rc->wall_x = wallx;
}

static int	calculate_tex_x(t_img *texture, t_raycaster *rc)
{
	int		tex_x;

	tex_x = 0;
	if (rc->impact_type != 'D')
		calculate_wall_x(rc);
	if ((rc->side == 0 && rc->ray_dir.x > 0)
		&& (rc->side == 1 && rc->ray_dir.y < 0))
		tex_x = texture->img_w - tex_x - 1;
	else
		tex_x = (int)(rc->wall_x * (double)(texture->img_w));
	return (tex_x);
}

static t_img	select_texture(t_cub3d *cub3d,
					t_player *player, t_raycaster *rc)
{
	t_img	texture;
	double	pos_diff_x;
	double	pos_diff_y;

	pos_diff_x = rc->map_pos.x - player->pos.x;
	pos_diff_y = rc->map_pos.y - player->pos.y;
	texture = cub3d->select_tex[3];
	if (pos_diff_y < 0 && rc->side == 1)
		texture = cub3d->select_tex[1];
	else if (pos_diff_y > 0 && rc->side == 1)
		texture = cub3d->select_tex[0];
	else if (pos_diff_x > 0 && rc->side == 0)
		texture = cub3d->select_tex[2];
	if (rc->impact_type == 'D')
		texture = cub3d->select_tex[6];
	return (texture);
}

void	calculate_texture_pixel(t_cub3d *cub3d, t_raycaster *rc, int x)
{
	t_vector	tex;
	double		tex_pos;
	t_img		texture;
	double		step;
	int			y;

	texture = select_texture(cub3d, &cub3d->player, rc);
	tex.x = calculate_tex_x(&texture, rc);
	step = 1.0 * texture.img_h / rc->line_height;
	tex_pos = (rc->draw_start - WINDOW_Y / 2 + rc->line_height / 2) * step;
	y = rc->draw_start;
	while (y < rc->draw_end)
	{
		tex.y = (int)tex_pos & (texture.img_h - 1);
		tex_pos += step;
		cub3d->buffer.data[(y * WINDOW_X) + x]
			= texture.data[texture.img_h * tex.y + tex.x];
		if (rc->side == 1)
			cub3d->buffer.data[(y * WINDOW_X) + x]
				= (cub3d->buffer.data[(y * WINDOW_X) + x] >> 1) & 8355711;
		y++;
	}
}
