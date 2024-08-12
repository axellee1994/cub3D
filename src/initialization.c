/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 14:21:58 by axlee             #+#    #+#             */
/*   Updated: 2024/08/06 12:53:49 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Game loop
int	game_loop(t_mlx *mlx)
{
	if (!mlx || !mlx->ply || !mlx->ray || !mlx->dt)
	{
		ft_putstr_fd("Error: Uninitialized game data\n", 2);
		return (1);
	}
	hook(mlx, 0, 0);
	cast_rays(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 0, 0);
	draw_minimap(mlx);
	if (mlx->show_help)
		display_help(mlx);
	return (0);
}

// Initialize the player
void	init_the_player(t_mlx *mlx)
{
	if (!mlx || !mlx->ply || !mlx->dt)
	{
		ft_putstr_fd("Error: Uninitialized player data\n", 2);
		return ;
	}
	mlx->ply->player_x = mlx->dt->player_x_position * TILE_SIZE + TILE_SIZE / 2;
	mlx->ply->player_y = mlx->dt->player_y_position * TILE_SIZE + TILE_SIZE / 2;
	mlx->ply->fov_rd = (FOV * PI) / 180;
	mlx->ply->angle = PI;
	mlx->ply->tilt = 0;
	mlx->ply->tilt_angle = 0;
	mlx->ply->proj_plane = (SCREEN_WIDTH / 2) / tan(mlx->ply->fov_rd / 2);
	mlx->ply->rot = 0;
	mlx->ply->left_to_right = 0;
	mlx->ply->up_to_down = 0;
}

// Start the game
void	start_the_game(t_data *dt)
{
	t_mlx	mlx;

	mlx.dt = dt;
	mlx.ply = malloc(sizeof(t_player) + sizeof(t_ray));
	if (!mlx.ply)
	{
		ft_putstr_fd("Error: Memory allocation failed\n", 2);
		free_and_exit(&mlx);
	}
	mlx.ray = (t_ray *)(mlx.ply + 1);
	ft_memset(mlx.ply, 0, sizeof(t_player) + sizeof(t_ray));
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D");
	mlx.img.img = mlx_new_image(mlx.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	init_image_buffer(&mlx);	
	init_the_player(&mlx);
	mlx.show_help = 0;
	mlx_loop_hook(mlx.mlx, game_loop, &mlx);
	mlx_hook(mlx.win, KeyPress, KeyPressMask, key_press, &mlx);
	mlx_hook(mlx.win, KeyRelease, KeyReleaseMask, key_release, &mlx);
	mlx_hook(mlx.win, 17, 0, free_and_exit, &mlx);
	mlx_loop(mlx.mlx);
}
