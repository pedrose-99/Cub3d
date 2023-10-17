/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 14:59:30 by pfuentes          #+#    #+#             */
/*   Updated: 2023/10/16 12:56:12 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3dbonus.h"

int	main(int argc, char **argv)
{
	t_cub3d	*cub3d;

	cub3d = NULL;
	if (argc != 2)
	{
		printf("Invalid number of arguments\n");
		return (1);
	}
	if (ft_rev_strncmp(argv[1], ".cub", 3))
	{
		printf("Bad file extension\n");
		return (1);
	}
	cub3d = set_cub3d(argv[1]);
	if (!cub3d)
		return (1);
	mlx_mouse_hide();
	mlx_mouse_move(cub3d->win, WINDOW_X / 2, WINDOW_Y / 2);
	render_frame(cub3d);
	waiting_events(cub3d);
	mlx_loop_hook(cub3d->mlx_ptr, &render_loop, cub3d);
	mlx_loop(cub3d->mlx_ptr);
	return (0);
}
