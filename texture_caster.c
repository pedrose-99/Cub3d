/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_caster.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 11:44:39 by pfuentes          #+#    #+#             */
/*   Updated: 2023/08/22 11:44:57 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	calculate_tex_x(t_img *texture, t_raycaster *rc)
{
	int		tex_x;
	double	wallx; //coordenada x o y exacta donde impactó el rayo

	tex_x = 0;
	if (rc->side == 0)
		wallx = rc->origin.y + rc->perp_wall_dist * rc->ray_dir.y;
	else
		wallx = rc->origin.x + rc->perp_wall_dist * rc->ray_dir.x;
	wallx -= floor((wallx));
	if ((rc->side == 0 && rc->ray_dir.x > 0)
		&& (rc->side == 1 && rc->ray_dir.y < 0))
		tex_x = texture->img_w - tex_x - 1;
	else
		tex_x = (int)(wallx * (double)(texture->img_w));
	return (tex_x);
}

static t_img	select_texture(t_cub3d *cub3d, t_player *player, t_raycaster *rc)
{
	t_img	texture;
	double	pos_diff_x;
	double	pos_diff_y;

	pos_diff_x = rc->map_pos.x - player->pos.x;
	pos_diff_y = rc->map_pos.y - player->pos.y;
	texture = cub3d->textures[3]->img; // textura oeste
	if (pos_diff_y < 0 && rc->side == 1) // textura sur
		texture = cub3d->textures[1]->img;
	else if (pos_diff_y > 0 && rc->side == 1) // textura norte
		texture = cub3d->textures[0]->img;	
	else if (pos_diff_x > 0 && rc->side == 0) // textura este
		texture = cub3d->textures[2]->img;
	return (texture);
}

void	calculate_texture_pixel(t_cub3d *cub3d, t_raycaster *rc, int x)
{
	int		tex_x;
	int		tex_y;
	double	tex_pos;
	t_img	texture;
	double	step;
	int		y;

	texture = select_texture(cub3d, cub3d->player, rc);
	tex_x = calculate_tex_x(&texture, rc);
	step = 1.0 * texture.img_h / rc->line_height;
	tex_pos = (rc->draw_start - WINDOW_Y / 2 + rc->line_height / 2) * step;
	y = rc->draw_start;
	while (y < rc->draw_end)
	{
        tex_y = (int)tex_pos & (texture.img_h - 1);
        tex_pos += step;
       	cub3d->buffer.data[(y * WINDOW_X) + x]
			= texture.data[texture.img_h * tex_y + tex_x];
        if (rc->side == 1)
			cub3d->buffer.data[(y * WINDOW_X) + x]
					= (cub3d->buffer.data[(y * WINDOW_X) + x] >> 1) & 8355711;
		y++;
	}
}
