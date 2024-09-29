/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:12:34 by axlee             #+#    #+#             */
/*   Updated: 2024/09/29 23:07:29 by jolai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Normalize the angle to be within 0 and 2*PI
double	nor_angle(double angle)
{
	angle = fmod(angle, 2 * PI);
	if (angle < 0)
		angle += 2 * PI;
	return (angle);
}

int	get_texture_color(double temp_x, double temp_y, t_img *texture)
{
	unsigned int	*pixel;
	int				x;
	int				y;

	if (!texture || texture->w == 0 || texture->h == 0)
	{
		ft_putstr_fd("Error: Invalid texture\n", STDERR_FILENO);
		return (0xFF0000);
	}
	x = (int)(texture->w * temp_x) % texture->w;
	y = (int)(texture->h * temp_y) % texture->h;
	if (x < 0 || x >= texture->w || y < 0 || y >= texture->h)
	{
		ft_putstr_fd("Warning: Texture coordinates out of bounds\n",
			STDERR_FILENO);
		return (0xFF00FF);
	}
	pixel = (unsigned int *)(texture->addr + (y * texture->line_length + x
				* (texture->bits_per_pixel / 8)));
	return (*pixel);
}

double	get_texture_intersect(t_mlx *mlx)
{
	double	intersect;

	if (mlx->ray->flag == 0)
		intersect = mlx->ply->player_y + mlx->ray->distance
			* sin(mlx->ray->ray_ngl);
	else
		intersect = mlx->ply->player_x + mlx->ray->distance
			* cos(mlx->ray->ray_ngl);
	intersect = fmod(intersect, TILE_SIZE) / TILE_SIZE;
	return (intersect);
}

void	draw_wall(t_mlx *mlx, int ray, int start, int end)
{
	int		y;
	double	tex_x;
	double	tex_y;

	tex_x = get_texture_intersect(mlx);
	y = fmax(0, start);
	while (y <= fmin(SCREEN_HEIGHT - 1, end))
	{
		tex_y = (double)(y - start) / (end - start);
		if (mlx->current_wall_color == 1)
			draw_pixel(mlx, ray, y,
				get_texture_color(tex_x, tex_y, mlx->dt->north));
		else if (mlx->current_wall_color == 2)
			draw_pixel(mlx, ray, y,
				get_texture_color(tex_x, tex_y, mlx->dt->east));
		else if (mlx->current_wall_color == 3)
			draw_pixel(mlx, ray, y,
				get_texture_color(1 - tex_x, tex_y, mlx->dt->south));
		else if (mlx->current_wall_color == 4)
			draw_pixel(mlx, ray, y,
				get_texture_color(1 - tex_x, tex_y, mlx->dt->west));
		else
			return ;
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
		draw_pixel(mlx, ray, i, mlx->dt->floor);
		i++;
	}
	i = 0;
	while (i < ceiling_height)
	{
		draw_pixel(mlx, ray, i, mlx->dt->ceiling);
		i++;
	}
}
