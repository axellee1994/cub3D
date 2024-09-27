/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:12:34 by axlee             #+#    #+#             */
/*   Updated: 2024/09/27 09:10:30 by axlee            ###   ########.fr       */
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

int	get_texture_color(double temp_x, double temp_y, t_img *texture)
{
	unsigned int	*pixel;
	int				x;
	int				y;

	if (!texture || texture->w == 0 || texture->h == 0)
	{
		ft_putstr_fd("Error: Invalid texture\n", STDERR_FILENO);
		return (0xFF0000);  // Return red for error visibility
	}
	x = (int)(texture->w * temp_x) % texture->w;
	y = (int)(texture->h * temp_y) % texture->h;
	if (x < 0 || x >= texture->w || y < 0 || y >= texture->h)
	{
		ft_putstr_fd("Warning: Texture coordinates out of bounds\n", STDERR_FILENO);
		return (0xFF00FF);  // Return magenta for error visibility
	}
	pixel = (unsigned int *)(texture->addr + (y * texture->line_length + x
				* (texture->bits_per_pixel / 8)));
	return (*pixel);
}

void	draw_wall(t_mlx *mlx, int ray, int start, int end)
{
	int		y;
	double	tex_x;
	double	tex_y;
	double	wall_x;
	t_img	*current_texture;

	if (mlx->ray->flag == 0) // Vertical intersection
		wall_x = mlx->ply->player_y + mlx->ray->distance
			* sin(mlx->ray->ray_ngl);
	else // Horizontal intersection
		wall_x = mlx->ply->player_x + mlx->ray->distance
			* cos(mlx->ray->ray_ngl);
	wall_x = fmod(wall_x, TILE_SIZE);
	tex_x = wall_x / TILE_SIZE;
	if (mlx->current_wall_color == 1)
		current_texture = mlx->dt->north;
	else if (mlx->current_wall_color == 2)
		current_texture = mlx->dt->east;
	else if (mlx->current_wall_color == 3)
	{
		current_texture = mlx->dt->south;
		tex_x = 1 - tex_x;
	}
	else if (mlx->current_wall_color == 4)
	{
		current_texture = mlx->dt->west;
		tex_x = 1 - tex_x;
	}
	else
		return ; // Invalid texture, should not happen
	y = fmax(0, start);
	while (y <= fmin(SCREEN_HEIGHT - 1, end))
	{
		tex_y = (double)(y - start) / (end - start);
		draw_pixel(mlx, ray, y, get_texture_color(tex_x, tex_y,
				current_texture));
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
