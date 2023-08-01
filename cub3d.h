/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 12:06:19 by pfuentes          #+#    #+#             */
/*   Updated: 2023/08/01 10:50:35 by pfuentes         ###   ########.fr       */
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

typedef enum e_texture_id{
	id_north = 1,
	id_south,
	id_east,
	id_west,
	id_color_floor,
	id_color_roof
}				t_texture_id;

typedef struct s_img
{
	void		*img_ptr;
	int			*data;
	int			size_l;
	int			bpp;
	int			endian;
}				t_img;

typedef struct s_texture{
	int		id;
	char	*file;
	t_img	img;
}	t_texture;

typedef struct s_color{
	int		id;
	int		rgb[3];
}	t_color;

typedef struct s_player
{
	int		x;
	int		y;
	int		pixel_x;
	int		pixel_y;
	int		to_move;
	int		to_move_x;
	int		to_move_y;
}			t_player;

typedef struct s_mlx
{
	void		*mlx_ptr;
	void		*win;
	t_img		**img;
	t_player	*player;
	char		**map;
}				t_mlx;


typedef struct s_cube3d{
	t_texture	textures[4];
	t_color		colors[2];
	char		**map;
}	t_cube3d;


char		**realloc_matrix(char **matrix, int len);
char		**init_matrix(char **matrix, int len);
char		**new_map(int fd);
void		print_map(char **map);

//textures-colors

int			set_textures_colors(t_cube3d *cub, char **data, char **dict);
int			set_texture_color(t_cube3d *cub, char *data, char **dict);
int			set_color(t_color *color, int id, char	*data);
t_texture	set_texture(int id, char	*data);

#endif