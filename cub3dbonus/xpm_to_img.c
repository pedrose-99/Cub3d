/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm_to_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 12:18:41 by pfuentes          #+#    #+#             */
/*   Updated: 2023/10/04 13:56:32 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3dbonus.h"

t_img	xpm_to_img(t_cub3d *cub3d, char *path)
{
	t_img	img;

	img.img_ptr = mlx_xpm_file_to_image(cub3d->mlx_ptr, path,
			&img.img_w, &img.img_h);
	if (!img.img_ptr)
	{
		free(img.img_ptr);
		exit(EXIT_FAILURE);
	}
	else
		img.data = (int *)mlx_get_data_addr(img.img_ptr, &img.bpp,
				&img.size_l, &img.endian);
	return (img);
}
