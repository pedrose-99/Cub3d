/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gestion_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pserrano <pserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 12:58:03 by pserrano          #+#    #+#             */
/*   Updated: 2023/08/22 12:05:34 by pserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_img	xpm_to_img(t_cub3d *cub3d, char *path)
{
	t_img	img;

	printf("Path: %s$\n", path);
	img.img_ptr = mlx_xpm_file_to_image(cub3d->mlx_ptr, path,
			&img.img_w, &img.img_h);
	if (!img.img_ptr)
	{
		printf("Mal img ptr\n");
		free(img.img_ptr);
		//exit(EXIT_FAILURE);
	}
	else
		img.data = (int *)mlx_get_data_addr(img.img_ptr, &img.bpp,
				&img.size_l, &img.endian);
	printf("Bien\n");
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
	return (texture);
}

static int	color_int(int t, int red, int green, int blue)
{
	return (t << 24 | red << 16 | green << 8 | blue);
}

//Arreglar
int	set_color(char	*data)
{
	int		start;
	int		end;
	int		cont;
	char	*color_str;
	int		color[3];

	if (str_char_num(data, ',') != 2)
	{
		printf("Número de comillas distinto de 2\n");
		return (-1);
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
			return (-1);
		}
		printf("Color_str: %s$\n", color_str);
		if (!ft_str_is_digit(color_str))
		{
			free(color_str);
			printf("Color_str tiene algo que no es dígito\n");
			return (-1);
		}
		color[cont] = ft_atoi(color_str);
		free(color_str);
		if (color[cont] < 0 || color[cont] > 255)
		{
			printf("Se sale del rango\n");
			return (-1);
		}
		start = ++end;
		cont++;
	}
	printf("RED: %d\n", color[0]);
	printf("GREEN: %d\n", color[1]);
	printf("BLUE: %d\n", color[2]);
	return (color_int(0, color[0], color[1], color[2]));
}
