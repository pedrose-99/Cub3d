/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 14:59:30 by pfuentes          #+#    #+#             */
/*   Updated: 2023/09/11 13:39:42 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

void	init_tex(t_cub3d *cub3d)
{
	int	pos;

	printf("Seleccionar texturas\n");
	pos = rand() % 3;
	printf("Pos: %d\n", pos);
	cub3d->select_tex[0] = cub3d->textures[pos];
	pos = rand() % 3;
	printf("Pos: %d\n", pos);
	cub3d->select_tex[1] = cub3d->textures[pos];
	pos = rand() % 3;
	printf("Pos: %d\n", pos);
	cub3d->select_tex[2] = cub3d->textures[pos];
	pos = rand() % 3;
	printf("Pos: %d\n", pos);
	cub3d->select_tex[3] = cub3d->textures[pos];
}

int	main(int argc, char **argv)
{
	t_cub3d	*cub3d;
	int		error;

	cub3d = NULL;
	if (argc != 2)
	{
		printf("Invalid number of arguments\n");
		return (1);
	}
	error = process_file(&cub3d, argv[1]);
	if (error != 0)
	{
		free_cub3d(cub3d, 0, error - 1);
		printf("Salir del programa\n");
		return (1);
	}
	cub3d->player = set_player(cub3d->map);
	mlx_mouse_hide();
	mlx_mouse_move(cub3d->win, WINDOW_X / 2, WINDOW_Y / 2);
	init_tex(cub3d);
	render_frame(cub3d);
	waiting_events(cub3d);
	mlx_loop_hook(cub3d->mlx_ptr, &render_loop, cub3d);
	mlx_loop(cub3d->mlx_ptr);
}
