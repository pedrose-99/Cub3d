/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3dbonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 12:06:19 by pfuentes          #+#    #+#             */
/*   Updated: 2023/10/04 13:58:43 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3DBONUS_H
# define CUB3DBONUS_H

# include <stdio.h>
# include <sys/fcntl.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdarg.h>
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
# define E_KEY 14
# define ESC 53

# define WINDOW_X 1920
# define WINDOW_Y 1080
# define RAY_MAX_DISTANCE 100

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

typedef struct s_floorcaster
{
	t_vector_d	ray_dir0;
	t_vector_d	ray_dir1;
	int			p;
	double		pos_z;
	double		row_distance;
	t_vector_d	floor_step;
	t_vector_d	floor_pos;
}	t_floorcaster;

typedef struct s_door
{
	t_vector	pos;
	double		border;
	int			move;
	int			open;
	int			view;
}	t_door;

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
	int			impact_type;
	double		wall_x;
}	t_raycaster;

typedef struct s_cub3d{
	void		*mlx_ptr;
	void		*win;
	t_player	player;
	t_img		textures[7];
	t_img		select_tex[7];
	char		**map;
	int			keys[7];
	t_list		*doors;
	t_img		buffer;
}	t_cub3d;

//cub3d
t_cub3d		*set_cub3d(char *file);
void		free_cub3d(t_cub3d *cub3d);

//map
char		**realloc_matrix(char **matrix, int len);
char		**init_matrix(int len);
char		**new_map(int fd);
char		**normalize_map(char **map);

//player
void		set_player(t_player *player, char **map);
void		move_player_pos(t_cub3d *cub3d, t_player *player,
				int sign, t_vector_d mult);
void		move_player_angle(t_player *player, int sign);

//raycasting
void		raycaster(t_cub3d *cub3d);
t_raycaster	init_ray(t_cub3d *cub3d, int x);
void		floorcaster(t_cub3d *cub3d);

//texturemapper
void		calculate_wall_x(t_raycaster *rc);
void		calculate_texture_pixel(t_cub3d *cub3d, t_raycaster *rc, int x);

//mlx
t_img		xpm_to_img(t_cub3d *cub3d, char *path);

//map checker
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
void		init_tex(t_cub3d *cub3d);
void		select_tex_animate(t_cub3d *cub3d);
int			render_frame(t_cub3d *cub3d);
int			render_loop(t_cub3d *cub3d);
void		buffer_ceilling_floor(t_cub3d *cub3d);
void		clear_buffer(t_cub3d *cub3d);

//doors
t_door		*new_door(int x, int y);
t_door		*find_door(t_list *doors, int x, int y);
t_list		*set_doors_lst(char **map);
void		move_door(t_cub3d *cub3d, t_list *doors, t_player *player);
void		animate_door(t_cub3d *cub3d, t_door *door);
void		animate_doors(t_cub3d *cub3d, t_list *doors);

//minimap
void		draw_minimap(t_cub3d *cub3d);

//mouse
void		check_mouse_move(t_cub3d *cub3d, t_player *player);

//utils
double		degree_to_radians(double degree);
char		**lst_to_matrix(t_list *lst);
void		free_lst_nodes(t_list *lst);

#endif