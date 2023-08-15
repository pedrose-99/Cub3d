/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 12:06:19 by pfuentes          #+#    #+#             */
/*   Updated: 2023/08/15 13:04:32 by pfuentes         ###   ########.fr       */
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

# define N 90
# define S 270
# define W 180
# define E 0
# define FOV 66

# define MOVE_UP 13
# define MOVE_DOWN 1
# define MOVE_LEFT 0
# define MOVE_RIGHT 2
# define ROT_LEFT 123
# define ROT_RIGHT 124
# define ESC 53

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
	char	*file;
	t_img	img;
}	t_texture;

typedef struct s_color{
	int		rgb[3];
}	t_color;

typedef struct s_vector{
	int	x;
	int	y;
}	t_vector;

typedef struct s_player
{
	float		x;
	float		y;
	int		angle;
	int		pixel_x;
	int		pixel_y;
	int		to_move;
	int		to_move_x;
	int		to_move_y;
}			t_player;

typedef struct s_cub3d{
	void		*mlx_ptr;
	void		*win;
	t_player	player;
	t_texture	**textures; //4
	t_color		**colors; //2
	char		**map;
	double		dirx;
	double		diry;
	double		planex;
	double		planey;
	double		rot_speed;
	double		move_speed;	
}	t_cub3d;


//cub3d

t_cub3d	*set_cub3d(void);
void	free_cub3d(t_cub3d *cub3d);
int		set_visual_data(t_cub3d *cub3d, int fd);

//map

char		**realloc_matrix(char **matrix, int len);
char		**init_matrix(int len);
char		**new_map(int fd);
void		print_matrix(char **matrix);
char		**normalize_map(char **map);

//textures-colors

t_color		*set_color(char	*data);
t_texture	*set_texture(t_cub3d *cub3d, char	*data);

//mlx

t_img		xpm_to_img(t_cub3d *cub3d, char *path);

//map.c
int			map_is_close(char **map);

#endif