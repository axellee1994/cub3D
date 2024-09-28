/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:59:40 by axlee             #+#    #+#             */
/*   Updated: 2024/09/28 15:30:44 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_rectangle(t_mlx *mlx, t_point pos, int size, int color)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < size)
	{
		while (j < size)
		{
			draw_pixel(mlx, pos.x + i, pos.y + j, color);
			j++;
		}
		j = 0;
		i++;
	}
}

void	draw_circle(t_mlx *mlx, t_point center, int radius, int color)
{
	int	x;
	int	y;
	int	dx;
	int	dy;

	x = center.x - radius;
	while (x <= center.x + radius)
	{
		y = center.y - radius;
		while (y <= center.y + radius)
		{
			dx = x - center.x;
			dy = y - center.y;
			if (dx * dx + dy * dy <= radius * radius)
				draw_pixel(mlx, x, y, color);
			y++;
		}
		x++;
	}
}

void	init_minimap(t_mlx *mlx, t_minimap *minimap)
{
	(void)mlx;
	minimap->width = 200;
	minimap->height = 200;
	minimap->tile_size = MINIMAP_TILE_SIZE;
	minimap->start_x = 10;
	minimap->start_y = 10;
}

void	draw_minimap_player(t_mlx *mlx, t_minimap *minimap)
{
	t_point	player_pos;

	player_pos.x = minimap->width / 2 + minimap->start_x;
	player_pos.y = minimap->height / 2 + minimap->start_y;
	draw_circle(mlx, player_pos, MINIMAP_PLAYER_SIZE, MINIMAP_PLAYER_COLOR);
}
