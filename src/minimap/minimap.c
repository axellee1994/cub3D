/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:11:13 by axlee             #+#    #+#             */
/*   Updated: 2024/09/28 16:00:03 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	draw_minimap_tile_at(t_mlx *mlx, t_minimap *minimap, int x, int y)
{
	t_point	pos;
	int		map_x;
	int		map_y;

	map_x = (mlx->ply->player_x / TILE_SIZE) - (minimap->width / (2
				* minimap->tile_size)) + x;
	map_y = (mlx->ply->player_y / TILE_SIZE) - (minimap->height / (2
				* minimap->tile_size)) + y;
	pos.x = x * minimap->tile_size + minimap->start_x;
	pos.y = y * minimap->tile_size + minimap->start_y;
	if (map_x >= 0 && map_x < mlx->dt->map_width && map_y >= 0
		&& map_y < mlx->dt->map_height)
	{
		if (mlx->dt->map2d[map_y][map_x] == '1')
			draw_rectangle(mlx, pos, minimap->tile_size, MINIMAP_WALL_COLOR);
		else
			draw_rectangle(mlx, pos, minimap->tile_size, MINIMAP_FLOOR_COLOR);
	}
	else
		draw_rectangle(mlx, pos, minimap->tile_size, MINIMAP_OUTSIDE_COLOR);
}

static void	draw_rectangle_outline(t_mlx *mlx, t_point pos, int size, int color)
{
	int	i;

	i = 0;
	while (i < size)
	{
		draw_pixel(mlx, pos.x + i, pos.y, color);
		draw_pixel(mlx, pos.x + i, pos.y + size - 1, color);
		draw_pixel(mlx, pos.x, pos.y + i, color);
		draw_pixel(mlx, pos.x + size - 1, pos.y + i, color);
		i++;
	}
}

static void	draw_minimap_recursive(t_mlx *mlx, t_minimap *minimap, int x, int y)
{
	if (y >= minimap->height / minimap->tile_size)
		return ;
	if (x < minimap->width / minimap->tile_size)
	{
		draw_minimap_tile_at(mlx, minimap, x, y);
		draw_minimap_recursive(mlx, minimap, x + 1, y);
	}
	else
		draw_minimap_recursive(mlx, minimap, 0, y + 1);
}

void	draw_minimap(t_mlx *mlx)
{
	t_minimap	minimap;
	t_point		border_pos;
	int			border_size;

	init_minimap(mlx, &minimap);
	draw_minimap_recursive(mlx, &minimap, 0, 0);
	draw_minimap_player(mlx, &minimap);
	draw_minimap_fov(mlx, &minimap);
	border_pos.x = minimap.start_x - 1;
	border_pos.y = minimap.start_y - 1;
	border_size = minimap.width;
	draw_rectangle_outline(mlx, border_pos, border_size, MINIMAP_BORDER_COLOR);
}
