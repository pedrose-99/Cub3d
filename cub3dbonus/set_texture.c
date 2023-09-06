/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 12:18:41 by pfuentes          #+#    #+#             */
/*   Updated: 2023/09/05 12:18:54 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_img	xpm_to_img(t_cub3d *cub3d, char *path)
{
	t_img	img;

	printf("Path: %s$\n", path);
	img.img_ptr = mlx_xpm_file_to_image(cub3d->mlx_ptr, path,
			&img.img_w, &img.img_h);
	printf("Hace img_ptr\n");
	if (!img.img_ptr)
	{
		printf("Mal img ptr\n");
		free(img.img_ptr);
		exit(EXIT_FAILURE);
	}
	else
		img.data = (int *)mlx_get_data_addr(img.img_ptr, &img.bpp,
				&img.size_l, &img.endian);
	printf("Bien img ptr\n");
	return (img);
}

t_img	set_texture(t_cub3d *cub3d, char	*data)
{
	t_img	texture;
	int		space_start;
	char	*file;

	space_start = move_to_char(data, ' ', 0);
	file = ft_strtrim(&data[space_start], " ");
	texture = xpm_to_img(cub3d, file);
	free(file);
	return (texture);
}
