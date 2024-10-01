/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 13:26:10 by axlee             #+#    #+#             */
/*   Updated: 2024/10/01 10:10:33 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Key press function
int	key_press(int keycode, t_mlx *mlx)
{
	if (keycode == ESC)
		free_and_exit(mlx);
	else if (keycode == A)
		mlx->ply->left_to_right = -1;
	else if (keycode == D)
		mlx->ply->left_to_right = 1;
	else if (keycode == S)
		mlx->ply->up_to_down = -1;
	else if (keycode == W)
		mlx->ply->up_to_down = 1;
	else if (keycode == LEFT)
		mlx->ply->rot = -1;
	else if (keycode == RIGHT)
		mlx->ply->rot = 1;
	else if (keycode == H)
		mlx->show_help = 1;
	else if (keycode == R)
		reset_player(mlx);
	return (0);
}

// Key release function
int	key_release(int keycode, t_mlx *mlx)
{
	if (keycode == A || keycode == D)
		mlx->ply->left_to_right = 0;
	else if (keycode == S || keycode == W)
		mlx->ply->up_to_down = 0;
	else if (keycode == LEFT || keycode == RIGHT)
		mlx->ply->rot = 0;
	else if (keycode == H)
		mlx->show_help = 0;
	return (0);
}

static void	calculate_movement(t_mlx *mlx, double *move_x, double *move_y)
{
	double	forward_x;
	double	forward_y;
	double	right_x;
	double	right_y;

	forward_x = cos(mlx->ply->angle) * PLAYER_SPEED;
	forward_y = sin(mlx->ply->angle) * PLAYER_SPEED;
	right_x = cos(mlx->ply->angle + PI / 2) * PLAYER_SPEED;
	right_y = sin(mlx->ply->angle + PI / 2) * PLAYER_SPEED;
	*move_x = 0;
	*move_y = 0;
	if (mlx->ply->up_to_down)
	{
		*move_x += forward_x * mlx->ply->up_to_down;
		*move_y += forward_y * mlx->ply->up_to_down;
	}
	if (mlx->ply->left_to_right)
	{
		*move_x += right_x * mlx->ply->left_to_right;
		*move_y += right_y * mlx->ply->left_to_right;
	}
}

void	hook(t_mlx *mlx, double move_x, double move_y)
{
	if (mlx->ply->rot)
		rotate_player(mlx, mlx->ply->rot * ROTATION_SPEED);
	calculate_movement(mlx, &move_x, &move_y);
	move_player(mlx, move_x, move_y);
}
