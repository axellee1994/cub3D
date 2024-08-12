/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:59:40 by axlee             #+#    #+#             */
/*   Updated: 2024/08/06 13:01:09 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	is_valid_point(t_mlx *mlx, int x, int y, int start_x, int start_y,
		int minimap_width)
{
	float world_x, world_y;

	if (x < start_x || x >= start_x + minimap_width || y < start_y
		|| y >= start_y + mlx->dt->map_height * MINIMAP_TILE_SIZE)
		return (0);

	world_x = (x - start_x) * (TILE_SIZE / MINIMAP_TILE_SIZE);
	world_y = (y - start_y) * (TILE_SIZE / MINIMAP_TILE_SIZE);

	return (wall_hit(world_x, world_y, mlx));
}
