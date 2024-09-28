/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 14:05:24 by axlee             #+#    #+#             */
/*   Updated: 2024/09/28 22:53:32 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// check the wall hit
int	wall_hit(double x, double y, t_mlx *mlx)
{
	int	x_m;
	int	y_m;

	if (x < 0 || y < 0)
		return (0);
	x_m = (int)floor(x / TILE_SIZE);
	y_m = (int)floor(y / TILE_SIZE);
	if (x_m < 0 || y_m < 0 || y_m >= mlx->dt->map_height
		|| x_m >= mlx->dt->map_width || !mlx->dt->map2d[y_m])
		return (0);
	if (mlx->dt->map2d[y_m] && x_m <= (int)strlen(mlx->dt->map2d[y_m]))
		if (mlx->dt->map2d[y_m][x_m] == '1')
			return (0);
	return (1);
}

void	cast_rays(t_mlx *mlx)
{
	double	h_inter;
	double	v_inter;
	int		ray;
	double	ray_angle;

	ray = 0;
	mlx->ray->ray_ngl = mlx->ply->angle - (mlx->ply->fov_rd / 2);
	while (ray < SCREEN_WIDTH)
	{
		mlx->ray->flag = 0;
		ray_angle = nor_angle(mlx->ray->ray_ngl);
		h_inter = get_h_inter(mlx, ray_angle);
		v_inter = get_v_inter(mlx, ray_angle);
		if (v_inter <= h_inter)
			mlx->ray->distance = v_inter;
		else
		{
			mlx->ray->distance = h_inter;
			mlx->ray->flag = 1;
		}
		render_wall(mlx, ray, mlx->ray->distance);
		ray++;
		mlx->ray->ray_ngl += (mlx->ply->fov_rd / SCREEN_WIDTH);
	}
}
