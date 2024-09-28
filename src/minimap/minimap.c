/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:11:13 by axlee             #+#    #+#             */
/*   Updated: 2024/09/28 13:09:45 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_minimap(t_mlx *mlx)
{
	t_minimap	minimap;
	t_point		pos;
	int			x;
	int			y;

	init_minimap(mlx, &minimap);
	y = 0;
	while (y < mlx->dt->map_height)
	{
		x = 0;
		while (x < mlx->dt->map_width)
		{
			pos.x = x;
			pos.y = y;
			if (mlx->dt->map2d[y][x] == '1')
				draw_minimap_tile(mlx, pos, MINIMAP_WALL_COLOR);
			else
				draw_minimap_tile(mlx, pos, MINIMAP_FLOOR_COLOR);
			x++;
		}
		y++;
	}
	draw_minimap_player(mlx, &minimap);
	draw_minimap_fov(mlx, &minimap);
}
