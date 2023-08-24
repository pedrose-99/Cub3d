/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 10:54:33 by pfuentes          #+#    #+#             */
/*   Updated: 2023/08/24 12:27:29 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_cub3d	*set_cub3d(void)
{
	t_cub3d	*cub3d;
	int		i;

	cub3d = (t_cub3d *)malloc(sizeof(t_cub3d));
	printf("Size of t_cub3d: %lu\n", sizeof(t_cub3d) * 8);
	cub3d->mlx_ptr = mlx_init();
	cub3d->win = mlx_new_window(cub3d->mlx_ptr, WINDOW_X, WINDOW_Y, "cub3d");
	cub3d->buffer.img_ptr = mlx_new_image(cub3d->mlx_ptr, WINDOW_X, WINDOW_Y);
	cub3d->buffer.data = (int *)mlx_get_data_addr(cub3d->buffer.img_ptr,
			&cub3d->buffer.bpp, &cub3d->buffer.size_l, &cub3d->buffer.endian);
	i = 0;
	while (i < 6)
	{
		cub3d->keys[i] = 0;
		i++;
	}
	return (cub3d);
}

void	free_image(void *mlx_ptr, t_img img)
{
	mlx_destroy_image(mlx_ptr, img.img_ptr);
}

void	free_textures(t_cub3d *cub3d)
{
	int	i;

	i = 0;
	printf("Liberar texturas\n");
	while (i < 4)
	{
		printf("Textura %d\n", i);
		if (cub3d->textures[i].img_ptr)
		{
			printf("Libera textura\n");
			//free_image(cub3d->mlx_ptr, cub3d->textures[i]);
			mlx_destroy_image(cub3d->mlx_ptr, cub3d->textures[i].img_ptr);
		}
		i++;
	}
}

void	free_mlx_data(t_cub3d *cub3d)
{
	printf("Liberar datos de cub3d\n");
	system("leaks -q cub3d");
	//free(cub3d->buffer.img_ptr);
	//free(cub3d->buffer.data);
	mlx_destroy_image(cub3d->mlx_ptr, cub3d->buffer.img_ptr);
	mlx_destroy_window(cub3d->mlx_ptr, cub3d->win);
	//free(cub3d->mlx_ptr);
	//cub3d->mlx_ptr = NULL;
	//free(cub3d->win);
	//cub3d->win = NULL;
	//system("leaks -q cub3d");
}

void	free_map(t_cub3d *cub3d)
{
	printf("Liberar mapa\n");
	free_matrix((void **)cub3d->map);
	cub3d->map = NULL;
}

void	free_player(t_cub3d *cub3d)
{
	printf("Liberar jugador\n");
	free(cub3d->player);
	cub3d->player = NULL;
}

void	free_cub3d(t_cub3d *cub3d, int start, int end)
{
	void	(*funcs[5])(t_cub3d*);
	printf("Liberar cub3d\n");
	funcs[0] = free_textures;
	funcs[1] = free_mlx_data;
	funcs[2] = free_map;
	funcs[3] = free_player;
	funcs[4] = NULL;
	while (funcs[start] && start <= end)
	{
		(*funcs[start])(cub3d);
		printf("Liberar cub3d %d\n", start);
		system("leaks -q cub3d");
		start++;
	}
	printf("Liberar cub3d: %p\n", &cub3d);
	//free(cub3d);
	//cub3d = NULL;
	exit(1);
}
