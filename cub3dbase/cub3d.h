/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 12:06:19 by pfuentes          #+#    #+#             */
/*   Updated: 2023/10/04 12:08:21 by pfuentes         ###   ########.fr       */
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
# include "minilibx_opengl_20191021/mlx.h"

# define N 90
# define S 270
# define W 180
# define E 0
# define FOV 90

# define MOVE_UP 13
# define MOVE_DOWN 1
# define MOVE_LEFT 0
# define MOVE_RIGHT 2
# define ROT_LEFT 123
# define ROT_RIGHT 124
# define ESC 53

# define CELL_UNIT 32
# define WINDOW_X 1280
# define WINDOW_Y 720
# define RAY_MAX_DISTANCE 100

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
	int			img_w;
	int			img_h;
	int			*data;
	int			size_l;
	int			bpp;
	int			endian;
}				t_img;

typedef struct s_vector{
	int	x;
	int	y;
}	t_vector;

typedef struct s_vector_d{
	double	x;
	double	y;
}	t_vector_d;

typedef struct s_player
{
	t_vector_d	pos;
	t_vector_d	dir;
	t_vector_d	plane;
	double		angle;
	double		camera_plane;
	double		rot_speed;
	double		move_speed;
}			t_player;

typedef struct s_raycaster
{
	t_vector_d	origin;
	t_vector_d	ray_dir;
	t_vector_d	ray_len;
	t_vector	map_pos;
	t_vector	map_len;
	t_vector_d	step_dir;
	t_vector_d	step_incr;
	double		camera_scale;
	int			side;
	double		perp_wall_dist;
	double		line_height;
	double		draw_start;
	double		draw_end;
}	t_raycaster;

typedef struct s_cub3d{
	void		*mlx_ptr;
	void		*win;
	t_player	player;
	t_img		textures[4];
	int			colors[2];
	char		**map;
	int			keys[6];
	t_img		buffer;
}	t_cub3d;

//cub3d
t_cub3d		*set_cub3d(void);
void		free_cub3d(t_cub3d *cub3d, int start, int end);
int			set_visual_data(t_cub3d *cub3d, int fd);

//file

void		print_errors_file(int error);
int			process_file(t_cub3d **cub3d, char *file);

//map

char		**realloc_matrix(char **matrix, int len);
char		**init_matrix(int len);
char		**new_map(int fd);
void		print_matrix(char **matrix);
char		**normalize_map(char **map);

//textures
t_img		set_texture(t_cub3d *cub3d, char	*data);

//colors
int			set_color(char	*data);

//player
void		set_player(t_player *player, char **map);
void		move_player_pos(t_player *player, int sign, t_vector_d mult);
void		move_player_angle(t_player *player, int sign);

//angles
double		degree_to_radians(double degree);

//raycasting
void		raycaster(t_cub3d *cub3d);
t_raycaster	init_ray(t_cub3d *cub3d, int x);

//texturemapper
void		calculate_texture_pixel(t_cub3d *cub3d, t_raycaster *rc, int x);

//mlx
t_img		xpm_to_img(t_cub3d *cub3d, char *path);

//map_checker
int			map_is_close(char **map);

//check char
int			not_char_alone(char **map, int i, int j);
int			check_char(char **map);

//keys
void		waiting_events(t_cub3d *cub3d);
void		key_funcs(t_cub3d *cub3d);
int			press_key(int key, t_cub3d *cub3d);
int			release_key(int key, t_cub3d *cub3d);
int			close_window(t_cub3d *cub3d);

//render

int			render_frame(t_cub3d *cub3d);
int			render_loop(t_cub3d *cub3d);
void		buffer_ceilling_floor(t_cub3d *cub3d);
void		clear_buffer(t_cub3d *cub3d);

//utils
char		**init_matrix(int len);
char		**lst_to_matrix(t_list *lst);
void		free_lst_nodes(t_list *lst);

#endif