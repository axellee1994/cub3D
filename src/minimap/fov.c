/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fov.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:06:52 by axlee             #+#    #+#             */
/*   Updated: 2024/09/28 13:47:01 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	draw_fov_line(t_mlx *mlx, t_minimap *minimap, double angle,
		int color)
{
	t_point	start;
	t_point	end;
	int		line_length;

	line_length = minimap->width / 6;
	start.x = (mlx->ply->player_x / TILE_SIZE) * minimap->tile_size
		+ minimap->start_x;
	start.y = (mlx->ply->player_y / TILE_SIZE) * minimap->tile_size
		+ minimap->start_y;
	end.x = start.x + cos(angle) * line_length;
	end.y = start.y + sin(angle) * line_length;
	draw_line(mlx, start, end, color);
}

static void	draw_fov_edges(t_mlx *mlx, t_minimap *minimap)
{
	double	fov_start_angle;
	double	fov_end_angle;

	fov_start_angle = mlx->ply->angle - (mlx->ply->fov_rd / 2);
	fov_end_angle = mlx->ply->angle + (mlx->ply->fov_rd / 2);
	draw_fov_line(mlx, minimap, fov_start_angle, FOV_LINE_COLOR);
	draw_fov_line(mlx, minimap, fov_end_angle, FOV_LINE_COLOR);
}

static void	draw_fov_middle(t_mlx *mlx, t_minimap *minimap)
{
	draw_fov_line(mlx, minimap, mlx->ply->angle, FOV_MIDDLE_LINE_COLOR);
}

void	draw_minimap_fov(t_mlx *mlx, t_minimap *minimap)
{
	draw_fov_edges(mlx, minimap);
	draw_fov_middle(mlx, minimap);
}
