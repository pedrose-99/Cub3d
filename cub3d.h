/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pserrano <pserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 12:06:19 by pfuentes          #+#    #+#             */
/*   Updated: 2023/07/31 11:16:10 by pserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <sys/fcntl.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdarg.h>
# include <mlx.h>
# include <math.h>
# include "libft/libft.h"

typedef enum	e_texture_id{
	id_north = 1,
	id_south,
	id_east,
	id_west,
	id_color_floor,
	id_color_roof
}				t_texture_id;

typedef struct s_texture{
	int		id;
	char	*file;
}	t_texture;

typedef struct s_color{
	int	id;
	int	rgb[3];
}	t_color;

typedef struct s_cube3d{
	t_texture	textures[4];
	t_color		colors[2];
	char		**map;
}	t_cube3d;

#endif