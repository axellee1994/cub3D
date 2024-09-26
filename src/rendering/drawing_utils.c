/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:12:34 by axlee             #+#    #+#             */
/*   Updated: 2024/09/26 18:13:27 by jolai            ###   ########.fr       */
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

void draw_wall(t_mlx *mlx, int ray, int start, int end)
{
    int y;
    double wall_height;
    double tex_x;
    double tex_y;
    double wall_x;

    wall_height = end - start;

    // Calculate the exact position where the ray hit the wall
    if (mlx->ray->flag == 0) // Vertical intersection
        wall_x = mlx->ply->player_y + mlx->ray->distance * sin(mlx->ray->ray_ngl);
    else // Horizontal intersection
        wall_x = mlx->ply->player_x + mlx->ray->distance * cos(mlx->ray->ray_ngl);
    wall_x = fmod(wall_x, TILE_SIZE);
    // Calculate the horizontal texture coordinate
    tex_x = wall_x / TILE_SIZE;
    y = fmax(0, start);
    while (y <= fmin(SCREEN_HEIGHT - 1, end))
    {
        // Calculate the vertical texture coordinate
        tex_y = (y - start) / wall_height;

        if (mlx->current_wall_color == 1)
            draw_pixel(mlx, ray, y, get_texture_color(tex_x, tex_y, mlx->dt->north));
        else if (mlx->current_wall_color == 2)
            draw_pixel(mlx, ray, y, get_texture_color(tex_x, tex_y, mlx->dt->east));
        else if (mlx->current_wall_color == 3)
            draw_pixel(mlx, ray, y, get_texture_color(1 - tex_x, tex_y, mlx->dt->south));
        else if (mlx->current_wall_color == 4)
            draw_pixel(mlx, ray, y, get_texture_color(1 - tex_x, tex_y, mlx->dt->west));
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
