/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:12:34 by axlee             #+#    #+#             */
/*   Updated: 2024/09/22 22:22:27 by jolai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Normalize the angle to be within 0 and 2*PI
float	nor_angle(float angle)
{
	while (angle < 0)
		angle += 2 * PI;
	while (angle >= 2 * PI)
		angle -= 2 * PI;
	return (angle);
}

int	get_texture_color(double temp_x, double temp_y, t_img *texture)//do i need to scale?
{
	unsigned int	*pixel;
	unsigned int	val;
	unsigned int	color;
	int				x;
	int				y;

//	printf("x: %f, y %f\n", temp_x, temp_y);
	x = (int) (texture->w * temp_x);
//	x = temp_x;
	y = (int) (texture->h * temp_y);
//	printf("converted x: %d, y %d\n", x, y);
	val = WALL_COLOR_NORTH;
//	if (temp_x < 0.1)
	pixel = (unsigned int *)(texture->addr
				+ (y * texture->line_length + x * (texture->bits_per_pixel / 8)));
//	else
//		pixel = &val;
	if (texture->endian != 0)
		color = (*pixel >> (texture->bits_per_pixel - 8)) & 0xFF;
	else
		color = (*pixel);
	return (color);
}
/*
map : render
x/block	:	y/(end - start)
y = (end - start) * (x / block)

render	:	texture
r/(end-start)	:	t / texture_size

t = texture_size * (r / (end - start))
t = texture_size * ((end - start) * (x / block) / (end - start))
t = texture_size * (x / block)

factors:
	intersect val
	texture width
	render size

something wrong with the scaling?????*/

void	draw_wall(t_mlx *mlx, int ray, int start, int end, double size)//change to add textures
{
	int		y;
	double	scale;

	scale = (end - start);//should it be tile_size instead?
	y = fmax(0, start);//this is top
//	if (mlx->ply->player_y == 30)//troubleshooting infinite loop
//		printf("Info: start:%d, end: %d, size: %f\n", start, end, size);
//	y = start;
//	while (y < end)// original
	while (y <= fmin(SCREEN_HEIGHT - 1, end))
	{
//		if (y == start)
//			draw_pixel(mlx, ray, y, GREEN);
//		else
//		draw_pixel(mlx, ray, y, (mlx->current_wall_color));
		if (mlx->current_wall_color == 1)
			draw_pixel(mlx, ray, y, get_texture_color(mlx->ray->h_intersect
				, (y - start) / scale, mlx->dt->north));
		else if (mlx->current_wall_color == 2)
			draw_pixel(mlx, ray, y, get_texture_color(mlx->ray->v_intersect
				, (y - start) / (scale), mlx->dt->east));
		else if (mlx->current_wall_color == 3)
			draw_pixel(mlx, ray, y, get_texture_color(mlx->ray->h_intersect
				, (y - start) / (scale), mlx->dt->south));
		else if (mlx->current_wall_color == 4)
			draw_pixel(mlx, ray, y, get_texture_color(mlx->ray->v_intersect
				, (y - start) / (scale), mlx->dt->west));
		y++;
	}
	(void) size;
}

void	draw_floor_ceiling(t_mlx *mlx, int ray, int ceiling_height,
		int floor_start)
{
	int	i;

	i = floor_start;
	while (i < SCREEN_HEIGHT)
	{
//		draw_pixel(mlx, ray, i, FLOOR_COLOR);
		draw_pixel(mlx, ray, i, mlx->dt->floor);
		i++;
	}
	i = 0;
	while (i < ceiling_height)
	{
//		draw_pixel(mlx, ray, i, CEILING_COLOR);
		draw_pixel(mlx, ray, i, mlx->dt->ceiling);
		i++;
	}
}
