/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gestion_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 12:58:03 by pserrano          #+#    #+#             */
/*   Updated: 2023/08/01 16:54:37 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_img	xpm_to_img(t_cub3d *cub3d, char *path)
{
	t_img	img;
	int		img_w;
	int		img_h;

	img.img_ptr = mlx_xpm_file_to_image(cub3d->mlx_ptr, path, &img_w, &img_h);
	if (!img.img_ptr)
	{
		free(img.img_ptr);
		//exit(EXIT_FAILURE);
	}
	else
		img.data = (int *)mlx_get_data_addr(img.img_ptr, &img.bpp,
				&img.size_l, &img.endian);
	return (img);
}

t_texture	set_texture(t_cub3d *cub3d, char	*data)
{
	t_texture	texture;
	int			space_start;

	space_start = move_to_char(data, ' ', 0);
	texture.file = ft_strtrim(&data[space_start], " ");
	texture.img = xpm_to_img(cub3d, texture.file);
	printf("FILE: %s$\n", texture.file);
	return (texture);
}

int	set_color(t_color *color, char	*data)
{
	int		start;
	int		i;
	char	**color_str;

	if (str_char_num(data, ',') != 2)
		return (0);
	start = skip_char(data, ' ', move_to_char(data, ' ', 0));
	color_str = ft_split(&data[start], ',');
	if (matrix_len(color_str) != 3)
		return (0);
	i = 0;
	while (color_str[i])
	{
		if (str_char_num(color_str[i], ' ') > 0
			|| !ft_str_is_digit(color_str[i]))
			return (0);
		color->rgb[i] = ft_atoi(color_str[i]);
		if (color->rgb[i] < 0 || color->rgb[i] > 255)
		{
			free_matrix((void **)color_str);
			return (0);
		}
		i++;
	}
	free_matrix((void **)color_str);
	return (1);
}

int	set_textures_colors(t_cub3d *cub3d, char **data)
{
	int		i;

	i = 0;
	while (data[i])
	{
		printf("Línea %d, %s\n", i, data[i]);
		if (i < 4)
			cub3d->textures[i] = set_texture(cub3d, data[i]);
		else
			if (!set_color(&cub3d->colors[i], data[i]))
				return (0);
		i++;
	}
	return (1);
}
