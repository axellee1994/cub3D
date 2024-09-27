/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:11:13 by axlee             #+#    #+#             */
/*   Updated: 2024/09/27 18:12:14 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_minimap(t_mlx *mlx)
{
	int	map_width;
	int	map_height;
	int	minimap_width;
	int	minimap_height;
	int	map_x;
	int	map_y;
	int	color;
	float	player_x;
	float	player_y;
	int	start_x;
	int	start_y;
	int	x;
	int	y;

	map_width = mlx->dt->map_width;
	map_height = mlx->dt->map_height;
	minimap_width = map_width * MINIMAP_TILE_SIZE;
	minimap_height = map_height * MINIMAP_TILE_SIZE;
	start_x = 10;
	start_y = 10;
	y = 0;
	while (y < minimap_height)
	{
		x = 0;
		while (x < minimap_width)
		{
			map_x = x / MINIMAP_TILE_SIZE;
			map_y = y / MINIMAP_TILE_SIZE;
			if (mlx->dt->map2d[map_y][map_x] == '1')
				color = MINIMAP_WALL_COLOR;
			else
				color = MINIMAP_FLOOR_COLOR;
			draw_pixel(mlx, start_x + x, start_y + y, color);
			x++;
		}
		y++;
	}
	player_x = (mlx->ply->player_x * MINIMAP_TILE_SIZE) / TILE_SIZE;
	player_y = (mlx->ply->player_y * MINIMAP_TILE_SIZE) / TILE_SIZE;
	y = -MINIMAP_PLAYER_SIZE;
	while (y <= MINIMAP_PLAYER_SIZE)
	{
		x = -MINIMAP_PLAYER_SIZE;
		while (x <= MINIMAP_PLAYER_SIZE)
		{
			if (x * x + y * y <= MINIMAP_PLAYER_SIZE * MINIMAP_PLAYER_SIZE)
			{
				draw_pixel(mlx, start_x + player_x + x, start_y + player_y + y,
					MINIMAP_PLAYER_COLOR);
			}
			x++;
		}
		y++;
	}
	y = 0;
	while (y <= minimap_height)
	{
		draw_pixel(mlx, start_x - 1, start_y + y, MINIMAP_BORDER_COLOR);
		draw_pixel(mlx, start_x + minimap_width, start_y + y,
			MINIMAP_BORDER_COLOR);
		y++;
	}
	x = 0;
	while (x <= minimap_width)
	{
		draw_pixel(mlx, start_x + x, start_y - 1, MINIMAP_BORDER_COLOR);
		draw_pixel(mlx, start_x + x, start_y + minimap_height,
			MINIMAP_BORDER_COLOR);
		x++;
	}
	draw_fov(mlx, start_x, start_y, minimap_width);
	printf("Player: (%f, %f), Minimap: (%f, %f)\n", 
		(float)mlx->ply->player_x, (float)mlx->ply->player_y, player_x, player_y);
}

void	find_endpoint(t_mlx *mlx, double angle, int *end_x, int *end_y,
		int start_x, int start_y, int player_x, int player_y, int fov_length,
		int minimap_width)
{
	int	i;

	i = 1;
	while (i <= fov_length)
	{
		*end_x = player_x + cos(angle) * i;
		*end_y = player_y + sin(angle) * i;
		if (!is_valid_point(mlx, start_x + *end_x, start_y + *end_y, start_x,
				start_y, minimap_width))
		{
			*end_x = player_x + cos(angle) * (i - 1);
			*end_y = player_y + sin(angle) * (i - 1);
			break ;
		}
		i++;
	}
}

void	draw_fov(t_mlx *mlx, int start_x, int start_y, int minimap_width)
{
	double fov_start;
	double fov_end;
	int player_x;
	int player_y;
	int fov_length;
	int left_end_x;
	int left_end_y;
	int right_end_x;
	int right_end_y;

	fov_start = nor_angle(mlx->ply->angle - mlx->ply->fov_rd / 2);
	fov_end = nor_angle(mlx->ply->angle + mlx->ply->fov_rd / 2);
	player_x = (mlx->ply->player_x * MINIMAP_TILE_SIZE) / TILE_SIZE;
	player_y = (mlx->ply->player_y * MINIMAP_TILE_SIZE) / TILE_SIZE;
	fov_length = minimap_width / 4; // Increased for better visibility
	find_endpoint(mlx, fov_start, &left_end_x, &left_end_y, start_x, start_y,
		player_x, player_y, fov_length, minimap_width);
	draw_line(mlx, start_x + player_x, start_y + player_y, start_x + left_end_x,
		start_y + left_end_y, 0xFF0000FF);
	find_endpoint(mlx, fov_end, &right_end_x, &right_end_y, start_x, start_y,
		player_x, player_y, fov_length, minimap_width);
	draw_line(mlx, start_x + player_x, start_y + player_y, start_x
		+ right_end_x, start_y + right_end_y, 0xFF0000FF);
	// Draw player direction line
	int dir_end_x, dir_end_y;
	find_endpoint(mlx, mlx->ply->angle, &dir_end_x, &dir_end_y, start_x,
		start_y, player_x, player_y, fov_length, minimap_width);
	draw_line(mlx, start_x + player_x, start_y + player_y, start_x + dir_end_x,
		start_y + dir_end_y, 0x00FF00FF); // Green color for direction
}
