/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 13:59:29 by axlee             #+#    #+#             */
/*   Updated: 2024/08/06 13:46:24 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Assign color of the wall based on the angle (Can be used for texturing)
int	get_wall_color(t_mlx *mlx, int flag)
{
	float	angle;

	angle = nor_angle(mlx->ray->ray_ngl);
	if (flag == 0)
	{
		if (angle > HALF_PI && angle < THREE_HALF_PI)
			return (WALL_COLOR_WEST);
		else
			return (WALL_COLOR_EAST);
	}
	else
	{
		if (angle > 0 && angle < PI)
			return (WALL_COLOR_SOUTH);
		else
			return (WALL_COLOR_NORTH);
	}
}

int	calculate_draw_position(int screen_height, double wall_height,
		int tilt_offset, int is_end)
{
	double	base_position;

	if (is_end)
		base_position = (screen_height / 2.0) + (wall_height / 2.0)
			+ tilt_offset;
	else
		base_position = (screen_height / 2.0) - (wall_height / 2.0)
			+ tilt_offset;
	if (is_end)
		return (fmin(screen_height - 1, base_position));
	else
		return (fmax(0, base_position));
}

void	render_wall(t_mlx *mlx, int ray, double distance)
{
	double	wall_height;
	int		tilt_offset;
	int		draw_start;
	int		draw_end;

	wall_height = (TILE_SIZE / distance) * mlx->ply->proj_plane;
	tilt_offset = (int)(mlx->ply->tilt_angle * SCREEN_HEIGHT);
	draw_start = calculate_draw_position(SCREEN_HEIGHT, wall_height,
			tilt_offset, 0);
	draw_end = calculate_draw_position(SCREEN_HEIGHT, wall_height, tilt_offset,
			1);
	mlx->current_wall_color = get_wall_color(mlx, mlx->ray->flag);
	draw_floor_ceiling(mlx, ray, draw_start, draw_end + 1);
	draw_wall(mlx, ray, draw_start, draw_end);
}
