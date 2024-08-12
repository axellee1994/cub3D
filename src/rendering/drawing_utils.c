/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:12:34 by axlee             #+#    #+#             */
/*   Updated: 2024/08/06 12:59:17 by axlee            ###   ########.fr       */
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

void	draw_wall(t_mlx *mlx, int ray, int start, int end)
{
	int	y;

	y = start;
	while (y <= end)
	{
		draw_pixel(mlx, ray, y, mlx->current_wall_color);
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
		draw_pixel(mlx, ray, i, FLOOR_COLOR);
		i++;
	}
	i = 0;
	while (i < ceiling_height)
	{
		draw_pixel(mlx, ray, i, CEILING_COLOR);
		i++;
	}
}
