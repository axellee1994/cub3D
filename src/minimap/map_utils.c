/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:59:40 by axlee             #+#    #+#             */
/*   Updated: 2024/09/30 12:15:32 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_rectangle(t_mlx *mlx, t_minimap pos, int size, int color)
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

void	draw_triangle(t_mlx *mlx, t_minimap center, int size, int color)
{
	double	angle;
	t_minimap	p1;
	t_minimap	p2;
	t_minimap	p3;

	angle = mlx->ply->angle;
	p1.x = center.x + cos(angle) * size / 2;
	p1.y = center.y + sin(angle) * size / 2;
	p2.x = center.x + cos(angle + 2.0944) * size / 2;
	p2.y = center.y + sin(angle + 2.0944) * size / 2;
	p3.x = center.x + cos(angle - 2.0944) * size / 2;
	p3.y = center.y + sin(angle - 2.0944) * size / 2;
	draw_line(mlx, p1, p2, color);
	draw_line(mlx, p2, p3, color);
	draw_line(mlx, p3, p1, color);
}

void	init_minimap(t_mlx *mlx, t_minimap *minimap)
{
	(void)mlx;
	minimap->width = 200;
	minimap->height = 200;
	minimap->tile_size = MINIMAP_TILE_SIZE * 1.5;
	minimap->start_x = 10;
	minimap->start_y = 10;
}

void	draw_minimap_player(t_mlx *mlx, t_minimap *minimap)
{
	t_minimap	player_pos;
	int		triangle_size;

	triangle_size = MINIMAP_PLAYER_SIZE * 2;
	player_pos.x = minimap->width / 2 + minimap->start_x;
	player_pos.y = minimap->height / 2 + minimap->start_y;
	draw_triangle(mlx, player_pos, triangle_size, MINIMAP_PLAYER_COLOR);
}
