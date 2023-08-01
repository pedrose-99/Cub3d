/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gestion_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 12:58:03 by pserrano          #+#    #+#             */
/*   Updated: 2023/08/01 10:40:25 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_img	xpm_to_img(t_mlx mlx, char *path)
{
	t_img	img;
	int		img_w;
	int		img_h;

	img.img_ptr = mlx_xpm_file_to_image(mlx.mlx_ptr, path, &img_w, &img_h);
	if (!img.img_ptr)
	{
		free(img.img_ptr);
		exit(EXIT_FAILURE);
	}
	img.data = (int *)mlx_get_data_addr(img.img_ptr, &img.bpp,
			&img.size_l, &img.endian);
	return (img);
}

t_texture	set_texture(int id, char	*data)
{
	t_texture	texture;
	int			space_start;

	texture.id = id;
	space_start = move_to_char(data, ' ', 0);
	texture.file = ft_strtrim(&data[space_start], " ");
	printf("ID: %d, FILE: %s$\n", texture.id, texture.file);
	return (texture);
}

int	set_color(t_color *color, int id, char	*data)
{
	int		start;
	int		end;
	int		cont;
	char	*color_str;

	color->id = id;
	if (str_char_num(data, ',') != 2)
		return (0);
	start = skip_char(data, ' ', move_to_char(data, ' ', 0));
	cont = 0;
	while (cont < 3)
	{
		end = move_to_char(data, ',', start);
		color_str = ft_substr(data, start, end - start);
		color->rgb[cont] = ft_atoi(color_str);
		free(color_str);
		if (color->rgb[cont] < 0 || color->rgb[cont] > 255)
			return (0);
		start = ++end;
		cont++;
	}
	printf("RED: %d\n", color->rgb[0]);
	printf("GREEN: %d\n", color->rgb[1]);
	printf("BLUE: %d\n", color->rgb[2]);
	return (1);
}

int	set_texture_color(t_cube3d *cub, char *data, char **dict)
{
	int	i;

	i = 0;
	if (!*data)
		return (-1);
	while (dict[i])
	{
		if (!ft_strncmp(data, dict[i], ft_strlen(dict[i])))
		{
			if (i < 4)
				cub->textures[i] = set_texture(i, data);
			else
				if (!set_color(&cub->colors[i], i - 4, data))
					return (0);
		}	
			i++;
	}
	return (1);
}

int	set_textures_colors(t_cube3d *cub, char **data, char **dict)
{
	int		i;
	int		count;
	int		check;

	i = 0;
	count = 0;
	while (data[i] && count < 6)
	{
		printf("Línea %d, %s\n", i, data[i]);
		check = set_texture_color(cub, data[i], dict);
		if (check == 1)
			count++;
		else if (check == 0)
			return (0);
		i++;
	}
	return (1);
}
