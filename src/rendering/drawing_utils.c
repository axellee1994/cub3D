/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:12:34 by axlee             #+#    #+#             */
/*   Updated: 2024/09/26 16:28:06 by axlee            ###   ########.fr       */
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

int get_texture_color(double temp_x, double temp_y, t_img *texture)
{
    unsigned int *pixel;
    unsigned int color;
    int x, y;

    x = (int)(texture->w * temp_x) % texture->w;
    y = (int)(texture->h * temp_y) % texture->h;

    pixel = (unsigned int *)(texture->addr
            + (y * texture->line_length + x * (texture->bits_per_pixel / 8)));

    color = *pixel;
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

void draw_wall(t_mlx *mlx, int ray, int start, int end)
{
    int y;
    double scale;
    double tex_x;
    double tex_y;
    double step;

    scale = end - start;
    step = 1.0 / scale;
    y = fmax(0, start);
    
    // Calculate the horizontal texture coordinate
    if (mlx->current_wall_color == 1 || mlx->current_wall_color == 3)
        tex_x = fmod(mlx->ray->h_intersect, 1.0);
    else
        tex_x = fmod(mlx->ray->v_intersect, 1.0);

    tex_y = 0.0;
    while (y <= fmin(SCREEN_HEIGHT - 1, end))
    {
        if (mlx->current_wall_color == 1)
            draw_pixel(mlx, ray, y, get_texture_color(tex_x, tex_y, mlx->dt->north));
        else if (mlx->current_wall_color == 2)
            draw_pixel(mlx, ray, y, get_texture_color(tex_x, tex_y, mlx->dt->east));
        else if (mlx->current_wall_color == 3)
            draw_pixel(mlx, ray, y, get_texture_color(tex_x, tex_y, mlx->dt->south));
        else if (mlx->current_wall_color == 4)
            draw_pixel(mlx, ray, y, get_texture_color(tex_x, tex_y, mlx->dt->west));
        y++;
        tex_y += step;
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
