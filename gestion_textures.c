/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gestion_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 12:58:03 by pserrano          #+#    #+#             */
/*   Updated: 2023/08/02 11:04:48 by pfuentes         ###   ########.fr       */
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

t_texture	*set_texture(t_cub3d *cub3d, char	*data)
{
	t_texture	*texture;
	int			space_start;

	texture = (t_texture *)malloc(sizeof(t_texture));
	space_start = move_to_char(data, ' ', 0);
	texture->file = ft_strtrim(&data[space_start], " ");
	texture->img = xpm_to_img(cub3d, texture->file);
	printf("FILE: %s$\n", texture->file);
	return (texture);
}

t_color	*set_color(char	*data)
{
	int		start;
	int		end;
	int		cont;
	char	*color_str;
	t_color	*color;

	color = (t_color *)malloc(sizeof(t_color));
	if (str_char_num(data, ',') != 2)
	{
		printf("Número de comillas distinto de 2\n");
		return (NULL);
	}
	start = skip_char(data, ' ', move_to_char(data, ' ', 0));
	cont = 0;
	while (cont < 3)
	{
		end = move_to_char(data, ',', start);
		color_str = ft_substr(data, start, end - start);
		if (!*color_str)
		{
			free(color_str);
			printf("No hay color_str, no hay nada antes de comilla\n");
			return (NULL);
		}
		printf("Color_str: %s$\n", color_str);
		if (!ft_str_is_digit(color_str))
		{
			free(color_str);
			printf("Color_str tiene algo que no es dígito\n");
			return (NULL);
		}
		color->rgb[cont] = ft_atoi(color_str);
		free(color_str);
		if (color->rgb[cont] < 0 || color->rgb[cont] > 255)
		{
			printf("Se sale del rango\n");
			return (NULL);
		}
		start = ++end;
		cont++;
	}
	printf("RED: %d\n", color->rgb[0]);
	printf("GREEN: %d\n", color->rgb[1]);
	printf("BLUE: %d\n", color->rgb[2]);
	return (color);
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
		{
			cub3d->colors[i - 4] = set_color(data[i]);
			if (!cub3d->colors[i - 4])
				return (0);
		}
		i++;
	}
	printf("Termina de setear texturas y colores\n");
	return (1);
}
