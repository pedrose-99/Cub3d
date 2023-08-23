/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 14:59:30 by pfuentes          #+#    #+#             */
/*   Updated: 2023/08/23 14:03:15 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	leaks(void)
{
	system("leaks -q cub3d");
}

int	main(int argc, char **argv)
{
	t_cub3d	*cub3d;
	int		error;

	atexit(&leaks);
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
	//draw_map(cub3d);
	waiting_events(cub3d);
	mlx_loop_hook(cub3d->mlx_ptr, &render_loop, cub3d);
	mlx_loop(cub3d->mlx_ptr);
}
