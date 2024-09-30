/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 15:31:14 by axlee             #+#    #+#             */
/*   Updated: 2024/09/30 20:54:06 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/includes/get_next_line.h"
# include "../libft/includes/libft.h"
# include <../mlx/mlx.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

// Game Environments
# define SCREEN_WIDTH 1920
# define SCREEN_HEIGHT 1010
# define TILE_SIZE 30
# define FOV 60
# define ROTATION_SPEED 0.045
# define PLAYER_SPEED 2
# define FPS_LIMIT 60
# define FRAME_TIME 0.016666667
# define MOUSE_SENSITIVITY 0.001

// Maths functions
# define PI 3.14159265358979323846
# define HALF_PI 1.57079632679
# define THREE_HALF_PI 4.71238898038

// Colours
# define BLACK 0x00000000
# define WHITE 0x00FFFFFF
# define RED 0x00FF0000
# define GREEN 0x0000FF00
# define BLUE 0x000000FF
# define AQUA 0x0000FFFF
# define MAGENTA 0xFFFF00FF

// Keyboard Mapping
# define UP 65362
# define DOWN 65364
# define LEFT 65361
# define RIGHT 65363
# define W 119
# define S 115
# define A 97
# define D 100
# define E 101
# define H 104
# define Q 113
# define R 114
# define M 109
# define SPACE 32
# define PLUS 65451
# define MINUS 65453
# define ESC 65307

// Minimap (COLOUR APPLICATION IS IN A,B,G,R)
# define MINIMAP_SCALE 0.2
# define MINIMAP_TILE_SIZE 6
# define MINIMAP_PLAYER_SIZE 3
# define MINIMAP_BORDER_COLOR 0xFFFFFFFF
# define MINIMAP_PLAYER_COLOR 0xFF0000FF
# define MINIMAP_WALL_COLOR 0x808080FF
# define MINIMAP_FLOOR_COLOR 0xFFFFFFFF
# define MINIMAP_OUTSIDE_COLOR 0xFF808080

// Player Structure
typedef struct s_player
{
	double			player_x;
	double			player_y;
	double			angle;
	float			fov_rd;
	int				rot;
	int				left_to_right;
	int				up_to_down;
	double			proj_plane;
	int				help;
}					t_player;

// Raycasting Structure
typedef struct s_ray
{
	double			ray_ngl;
	double			distance;
	int				flag;
}					t_ray;

// Image Structure
typedef struct s_img
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				h;
	int				w;
}					t_img;

// Data Structure
typedef struct s_data
{
	char			**map2d;
	int				player_x_position;
	int				player_y_position;
	int				map_width;
	int				map_height;
	t_img			*north;
	t_img			*south;
	t_img			*west;
	t_img			*east;
	unsigned int	floor;
	unsigned int	ceiling;
}					t_data;

// Minimap Structure
typedef struct s_minimap
{
	int				width;
	int				height;
	int				tile_size;
	int				start_x;
	int				start_y;
	double			scale;
	int				x;
	int				y;
}					t_minimap;

// Struct for line drawing
typedef struct s_line_data
{
	int				dx;
	int				dy;
	int				sx;
	int				sy;
	int				err;
}					t_line_data;

// MLX Structure
typedef struct s_mlx
{
	void			*mlx;
	void			*win;
	t_img			img;
	t_ray			*ray;
	t_data			*dt;
	t_player		*ply;
	int				show_help;
	int				current_wall_color;
	int				mouse_enabled;
}					t_mlx;

// Scene Structure
typedef struct s_scene
{
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	char			**floor;
	char			**ceiling;
	char			**map;
}					t_scene;

/******************************************************************************
	Function prototypes
******************************************************************************/

//main
t_data				*process_map(t_scene *scene);
int					check_and_initialize(int argc, char **argv, t_data **data,
						t_scene **scene);

// initialization
int					game_loop(t_mlx *mlx);
void				init_the_player(t_mlx *mlx);
void				start_the_game(t_data *dt, t_scene *scene);

// init_texture
unsigned int		convert_rgb(int r, int g, int b);
t_img				*new_texture(t_mlx *mlx, char *tex_file);
int					init_single_texture(t_mlx *mlx, t_img **texture, char *file,
						char *direction);
int					init_wall_texture(t_mlx *mlx, t_scene *scene);
void				init_textures(t_mlx *mlx, t_scene *scene);

// player
double				init_player_orientation(t_mlx *mlx);
void				reset_player(t_mlx *mlx);
void				rotate_player(t_mlx *mlx, float angle);
void				move_player(t_mlx *mlx, double move_x, double move_y);

// hooks
int					key_press(int keycode, t_mlx *mlx);
int					key_release(int keycode, t_mlx *mlx);
int					mouse_rotation(int x, int y, t_mlx *mlx);
void				hook(t_mlx *mlx, double move_x, double move_y);

// help
void				display_help(t_mlx *mlx);

// free_and_exit
void				free_textures(t_mlx *mlx);
void				free_map_data(t_data *dt);
int					free_and_exit(t_mlx *mlx);

/*************************************
		Loading
*************************************/

// input_file
int					valid_map_elem(char *map);
int					valid_num_player_pos(char *map);
int					read_map(int fd, char *line, t_scene *scene);
int					read_details(int fd, t_scene *scene);
t_scene				*read_cub_file(char *file);

// scene_loading
int					get_tex_file(char *line, t_scene *scene);
int					get_color_val(char *line, t_scene *scene);
int					get_tex_info(char *line, t_scene *scene);
char				*read_texture(int fd, t_scene **scene);

// loading_utils
char				*ft_strjoin_free(char *s1, char *s2);
int					is_empty_line(char *line);
int					is_tex_info(char *line);
void				free_scene(t_scene *scene);
void				load_error(char *msg, char *line, char **arr,
						t_scene *scene);

// check_scene
int					check_color_val(char **arr);
int					check_tex_file(char *file);
int					check_scene(t_scene *det);

// process_map
int					get_map_dimensions(char **map, t_data *data);
void				get_player_position(char **map, t_data *data);
void				assign_map_value(char **prev, char *line, int row,
						t_data *data);
char				**convert_map(char **prev, t_data *data);
void				map_fill(int x, int y, t_data *data, int *valid);

/*************************************
		Raycasting
*************************************/

// angle_utils
int					unit_circle(float angle, char c);

// intersection_utils
int					inter_check(float angle, float *inter, float *step,
						int is_horizon);

// intersection
float				get_h_inter(t_mlx *mlx, float angl);
float				get_v_inter(t_mlx *mlx, float angl);

// raycasting
int					wall_hit(double x, double y, t_mlx *mlx);
void				cast_rays(t_mlx *mlx);

/*************************************
		Rendering
*************************************/

// pixel_utils
void				init_image_buffer(t_mlx *mlx);
void				draw_pixel(t_mlx *mlx, int x, int y, int color);

// drawing_utils
double				nor_angle(double angle);
int					get_texture_color(double temp_x, double temp_y,
						t_img *texture);
double				get_texture_intersect(t_mlx *mlx);
void				draw_wall(t_mlx *mlx, int ray, int start, int end);
void				draw_floor_ceiling(t_mlx *mlx, int ray, int ceiling_height,
						int floor_start);

// rendering
int					get_wall_color(t_mlx *mlx, int flag);
int					calculate_draw_position(int screen_height,
						double wall_height, int is_end);
void				render_wall(t_mlx *mlx, int ray, double distance);

/*************************************
		Minimap
*************************************/

// draw_line
void				draw_line(t_mlx *mlx, t_minimap start, t_minimap end,
						int color);

// map_utils
void				draw_rectangle(t_mlx *mlx, t_minimap pos, int size,
						int color);
void				draw_triangle(t_mlx *mlx, t_minimap center, int size,
						int color);
void				init_minimap(t_mlx *mlx, t_minimap *minimap);
void				draw_minimap_player(t_mlx *mlx, t_minimap *minimap);

// minimap
void				draw_minimap(t_mlx *mlx);

#endif
