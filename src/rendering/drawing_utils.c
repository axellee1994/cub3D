/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:12:34 by axlee             #+#    #+#             */
/*   Updated: 2024/09/20 17:51:52 by jolai            ###   ########.fr       */
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
	unsigned int	color;
	int				x;
	int				y;

	x = texture->w * temp_x;
	y = texture->h * temp_y;
	pixel = (unsigned int *)(texture->addr
			+ (y * texture->line_length + x * (texture->bits_per_pixel / 8)));
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
something wrong with the scaling?????*/

void	draw_wall(t_mlx *mlx, int ray, int start, int end)//change to add textures
{
	int		y;
	double	scale;

	scale = (end - start);//should it be tile_size instead?
	y = start;//this is top
	while (y <= end)
	{
//		if (y == start)
//			draw_pixel(mlx, ray, y, GREEN);
//		else
//		draw_pixel(mlx, ray, y, (mlx->current_wall_color));
		if (mlx->current_wall_color == 1)
			draw_pixel(mlx, ray, y, get_texture_color(mlx->ray->h_intersect
				, (y - start) / (scale), mlx->dt->north));
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
