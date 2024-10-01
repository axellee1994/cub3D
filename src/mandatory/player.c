/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 14:42:49 by axlee             #+#    #+#             */
/*   Updated: 2024/09/29 18:51:54 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

double	init_player_orientation(t_mlx *mlx)
{
	char	c;

	c = mlx->dt->map2d[mlx->dt->player_y_position][mlx->dt->player_x_position];
	if (c == 'n')
		return (THREE_HALF_PI);
	else if (c == 's')
		return (HALF_PI);
	else if (c == 'e')
		return (0);
	else if (c == 'w')
		return (PI);
	return (0);
}

// Reset the player
void	reset_player(t_mlx *mlx)
{
	mlx->ply->player_x = mlx->dt->player_x_position * TILE_SIZE + TILE_SIZE / 2;
	mlx->ply->player_y = mlx->dt->player_y_position * TILE_SIZE + TILE_SIZE / 2;
	mlx->ply->angle = init_player_orientation(mlx);
	mlx->ply->rot = 0;
	mlx->ply->left_to_right = 0;
	mlx->ply->up_to_down = 0;
}

// Rotate player
void	rotate_player(t_mlx *mlx, float angle)
{
	mlx->ply->angle += angle;
	mlx->ply->angle = nor_angle(mlx->ply->angle);
}

// Move player
void	move_player(t_mlx *mlx, double move_x, double move_y)
{
	double	new_x;
	double	new_y;
	int		map_grid_x;
	int		map_grid_y;

	new_x = mlx->ply->player_x + move_x;
	new_y = mlx->ply->player_y + move_y;
	map_grid_x = (int)(new_x / TILE_SIZE);
	map_grid_y = (int)(new_y / TILE_SIZE);
	if (mlx->dt->map2d[map_grid_y][map_grid_x] != '1'
		&& mlx->dt->map2d[map_grid_y][(int)(mlx->ply->player_x
			/ TILE_SIZE)] != '1' && mlx->dt->map2d[(int)(mlx->ply->player_y
			/ TILE_SIZE)][map_grid_x] != '1')
	{
		mlx->ply->player_x = new_x;
		mlx->ply->player_y = new_y;
	}
}
