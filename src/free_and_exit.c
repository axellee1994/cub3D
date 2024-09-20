/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 13:17:21 by axlee             #+#    #+#             */
/*   Updated: 2024/09/04 15:43:59 by jolai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Free the texture data
void	free_textures(t_mlx *mlx)
{
	if (!mlx ||!(mlx->dt))
		return ;
	if (mlx->dt->north)
	{
		mlx_destroy_image(mlx->mlx, mlx->dt->north->img);
		free(mlx->dt->north);
	}
	if (mlx->dt->south)
	{
		mlx_destroy_image(mlx->mlx, mlx->dt->south->img);
		free(mlx->dt->south);
	}
	if (mlx->dt->east)
	{
		mlx_destroy_image(mlx->mlx, mlx->dt->east->img);
		free(mlx->dt->east);
	}
	if (mlx->dt->west)
	{
		mlx_destroy_image(mlx->mlx, mlx->dt->west->img);
		free(mlx->dt->west);
	}
}

// Free the map data
void	free_map_data(t_data *dt)
{
	int	i;

	if (!dt)
		return ;
	if (dt->map2d)
	{
		i = 0;
		while (dt->map2d[i])
		{
			free(dt->map2d[i]);
			i++;
		}
		free(dt->map2d);
	}
	free(dt);
}

// Free and exit the game
int	free_and_exit(t_mlx *mlx)
{
	if (mlx)
	{
		free_textures(mlx);
		free_map_data(mlx->dt);
		free(mlx->ply);
		if (mlx->mlx)
		{
			if (mlx->img.img)
				mlx_destroy_image(mlx->mlx, mlx->img.img);
			if (mlx->win)
				mlx_destroy_window(mlx->mlx, mlx->win);
			mlx_destroy_display(mlx->mlx);
			free(mlx->mlx);
		}
		printf("Thanks for playing the game!\n");
	}
	exit(0);
}
