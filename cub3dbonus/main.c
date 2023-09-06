/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pserrano <pserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 14:59:30 by pfuentes          #+#    #+#             */
/*   Updated: 2023/09/06 11:30:15 by pserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	//draw_map(cub3d);
	waiting_events_aux(cub3d);
	mlx_loop_hook(cub3d->mlx_ptr, &render_loop, cub3d);
	mlx_loop(cub3d->mlx_ptr);
}
