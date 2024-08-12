/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 13:26:10 by axlee             #+#    #+#             */
/*   Updated: 2024/08/06 12:54:07 by axlee            ###   ########.fr       */
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
	else if (keycode == UP)
		mlx->ply->tilt = 1;
	else if (keycode == DOWN)
		mlx->ply->tilt = -1;
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
	else if (keycode == UP || keycode == DOWN)
		mlx->ply->tilt = 0;
	else if (keycode == H)
		mlx->show_help = 0;
	return (0);
}

// Hook function
void	hook(t_mlx *mlx, double move_x, double move_y)
{
	double	cos_angle;
	double	sin_angle;

	cos_angle = cos(mlx->ply->angle);
	sin_angle = sin(mlx->ply->angle);
	if (mlx->ply->rot)
		rotate_player(mlx, mlx->ply->rot);
	if (mlx->ply->left_to_right)
	{
		move_x = -sin_angle * PLAYER_SPEED * mlx->ply->left_to_right;
		move_y = cos_angle * PLAYER_SPEED * mlx->ply->left_to_right;
	}
	if (mlx->ply->up_to_down)
	{
		move_x = cos_angle * PLAYER_SPEED * mlx->ply->up_to_down;
		move_y = sin_angle * PLAYER_SPEED * mlx->ply->up_to_down;
	}
	if (mlx->ply->tilt)
	{
		mlx->ply->tilt_angle += TILT_SPEED * mlx->ply->tilt;
		mlx->ply->tilt_angle = fmax(-MAX_TILT, fmin(MAX_TILT,
					mlx->ply->tilt_angle));
	}
	move_player(mlx, move_x, move_y);
}
