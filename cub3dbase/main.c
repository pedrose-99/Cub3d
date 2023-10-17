/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 14:59:30 by pfuentes          #+#    #+#             */
/*   Updated: 2023/10/16 09:32:11 by pfuentes         ###   ########.fr       */
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
		print_errors_file(error);
		free_cub3d(cub3d, 0, error);
		cub3d = NULL;
		return (1);
	}
	set_player(&cub3d->player, cub3d->map);
	waiting_events(cub3d);
	mlx_loop_hook(cub3d->mlx_ptr, &render_loop, cub3d);
	mlx_loop(cub3d->mlx_ptr);
}
