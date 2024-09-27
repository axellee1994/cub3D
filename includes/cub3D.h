/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 15:31:14 by axlee             #+#    #+#             */
/*   Updated: 2024/09/27 18:28:43 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/includes/libft.h"
# include "../libft/includes/get_next_line.h"
# include <../mlx/mlx.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>

// Game Environments
# define SCREEN_WIDTH 1920    // screen width
# define SCREEN_HEIGHT 1080   // screen height
# define TILE_SIZE 30         // tile size
# define FOV 60               // field of view
# define ROTATION_SPEED 0.045 // rotation speed
# define PLAYER_SPEED 2       // player speed
# define TILT_SPEED 0.01
# define MAX_TILT 0.5 // 30 degrees, adjust as needed
# define FPS_LIMIT 60
# define FRAME_TIME (1.0 / FPS_LIMIT)

// Maths functions
# define PI 3.14159265358979323846
# define HALF_PI (PI / 2)
# define THREE_HALF_PI (3 * PI / 2)

// Colours
# define BLACK 0x00000000
# define WHITE 0x00FFFFFF
# define RED 0x00FF0000
# define GREEN 0x0000FF00
# define BLUE 0x000000FF

// Color definitions
# define CEILING_COLOR 0x89CFF3FF // Light blue
# define FLOOR_COLOR 0xB99470FF   // Light brown

// Wall colors
# define WALL_COLOR_EAST 0xB5B5B5FF  // Light gray
# define WALL_COLOR_WEST 0xB5B5B5FF  // Light gray
# define WALL_COLOR_NORTH 0xF5F5F5FF // Very light gray (almost white)
# define WALL_COLOR_SOUTH 0xF5F5F5FF // Very light gray (almost white)

// Door colors
# define MINIMAP_DOOR_CLOSED_COLOR 0x00FF00 // Green
# define MINIMAP_DOOR_OPEN_COLOR 0x008000   // Dark Green
# define DOOR_CLOSED_COLOR 0x8B4513         // Saddle Brown
# define DOOR_OPEN_COLOR 0xD2691E           // Chocolate

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
# define C 99
# define V 118
# define SPACE 32
# define PLUS 65451
# define MINUS 65453
# define ESC 65307

// Minimap
# define MINIMAP_SCALE 0.2 // Scale of the minimap relative to the main view
# define MINIMAP_TILE_SIZE (TILE_SIZE * MINIMAP_SCALE)
# define MINIMAP_PLAYER_SIZE 4
# define MINIMAP_BORDER_COLOR 0x000000FF // Black
# define MINIMAP_PLAYER_COLOR 0xFF0000FF // Red
# define MINIMAP_WALL_COLOR 0x808080FF   // Gray
# define MINIMAP_FLOOR_COLOR 0xFFFFFFFF  // White

// Replace all instances of M_PI with PI in your code
typedef struct s_player // the player structure
{
	double player_x;      // player x position in pixels
	double player_y;      // player y position in pixels
	double angle;      // player angle
	float fov_rd;      // field of view in radians
	int rot;           // rotation flag
	int left_to_right; // left right flag
	int up_to_down;    // up down flag
	int tilt;
	double tilt_angle;
	double proj_plane;
	int help;
}			t_player;

typedef struct s_ray // the ray structure
{
	double	ray_ngl;  // ray angle
	double	distance; // distance to the wall
	double	h_intersect;
	double	v_intersect;
	int		flag;        // flag for the wall
}			t_ray;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		h;
	int		w;
}			t_img;

typedef struct s_data // the data structure
{
	char **map2d;			// the map
	int player_x_position;	// player x position in the map
	int player_y_position;	// player y position in the map
	int map_width;			// map width
	int map_height;			// map height
	t_img			*north;	// north wall texture
	t_img			*south;	// south wall texture
	t_img			*west;	// west wall texture
	t_img			*east;	// east wall texture
	unsigned int	floor;	// floor color
	unsigned int	ceiling;//ceiling color
}			t_data;

typedef struct s_minimap_coords
{
	int		x;
	int		y;
	int		start_x;
	int		start_y;
	int		width;
}			t_minimap_coords;

typedef struct s_mlx // the mlx structure
{
	void *mlx;     // the mlx pointer
	void *win;     // the window pointer
	t_img img;     // the image structure
	t_ray *ray;    // the ray structure
	t_data *dt;    // the data structure
	t_player *ply; // the player structure
	int show_help;
	int current_wall_color;
}			t_mlx;

typedef struct s_scene
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	char	**floor;
	char	**ceiling;
	char	**map;
}			t_scene;

/*typedef struct s_info
{
	t_img			*north;
	t_img			*south;
	t_img			*west;
	t_img			*east;
	unsigned int	floor;
	unsigned int	ceiling;
	char			**map;
}			t_info;*/

// minimap_fov_lines
void		draw_line(t_mlx *mlx, int x1, int y1, int x2, int y2, int color);

// minimap_map_utils
int			is_valid_point(t_mlx *mlx, int x, int y, int start_x, int start_y,
				int minimap_width);

// minimap
void		draw_minimap(t_mlx *mlx);
void		find_endpoint(t_mlx *mlx, double angle, int *end_x, int *end_y,
				int start_x, int start_y, int player_x, int player_y,
				int fov_length, int minimap_width);
void		draw_fov(t_mlx *mlx, int start_x, int start_y, int minimap_width);

// raycasting
int			unit_circle(float angle, char c);
int			inter_check(float angle, float *inter, float *step, int is_horizon);
float		get_h_inter(t_mlx *mlx, float angl);
float		get_v_inter(t_mlx *mlx, float angl);
int			wall_hit(double x, double y, t_mlx *mlx);
void		cast_rays(t_mlx *mlx);


// free_and_exit
void		free_textures(t_mlx *mlx);
void		free_map_data(t_data *dt);
int			free_and_exit(t_mlx *mlx);

// hooks
int			key_press(int keycode, t_mlx *mlx);
int			key_release(int keycode, t_mlx *mlx);
void		hook(t_mlx *mlx, double move_x, double move_y);

// player
double		init_player_orientation(t_mlx *mlx);
void		reset_player(t_mlx *mlx);
void		rotate_player(t_mlx *mlx, int direction);
void		move_player(t_mlx *mlx, double move_x, double move_y);

// rendering
void		init_image_buffer(t_mlx *mlx);
void		draw_pixel(t_mlx *mlx, int x, int y, int color);
double		nor_angle(double angle);
//void		draw_wall(t_mlx *mlx, int ray, int start, int end);
void		draw_floor_ceiling(t_mlx *mlx, int ray, int ceiling_height,
				int floor_start);
int			get_wall_color(t_mlx *mlx, int flag);
void		draw_wall(t_mlx *mlx, int ray, int top_pixel, int bottom_pixel);
void		render_wall(t_mlx *mlx, int ray, double adjusted_distance);

// raycasting
void		cast_rays(t_mlx *mlx);
float		get_v_inter(t_mlx *mlx, float angl);
float		get_h_inter(t_mlx *mlx, float angl);
int			inter_check(float angle, float *inter, float *step, int is_horizon);
int			unit_circle(float angle, char c);

// initialization
int			game_loop(t_mlx *mlx);
t_data		*init_argument(char *map_file);
int			check_and_initialize(int argc, char **argv, t_data **data, t_scene **scene);
void		init_the_player(t_mlx *mlx);
void		start_the_game(t_data *dt, t_scene *scene);

// Validations
int			validate_map(t_data *data);
int			check_player_position(t_data *data, int y, int x,
				int *player_count);
int			validate_player_position(t_data *data);

// Input_file
void		free_details(t_scene *det);
t_scene		*read_cub_file(char *file);

// Check scene
int			check_color_val(char **arr);
int			check_tex_file(char *file);
int			check_scene(t_scene *det);

// Map elem checks
int			valid_map_elem(char *map);
int			valid_num_player_pos(char *map);
void		get_map_dimensions(char **map, t_data *data);
void		get_player_position(char **map, t_data *data);
char		**convert_map(char **prev, t_data *data);
t_data		*process_map(t_scene *scene);

//load_texture
unsigned int	convert_rgb(int r, int g, int b);
t_img			*new_texture(t_mlx *mlx, char *tex_file);
int				load_wall_texture(t_mlx *mlx, t_scene *scene);
int	load_single_texture(t_mlx *mlx, t_img **texture, char *file, char *direction);
void			init_textures(t_mlx *mlx, t_scene *scene);

// help
void		display_help(t_mlx *mlx);

//test_utils
void		print_details(t_scene *details);
#endif
