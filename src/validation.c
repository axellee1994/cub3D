/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:23:05 by axlee             #+#    #+#             */
/*   Updated: 2024/09/28 23:03:06 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Validate the map
int	validate_map(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < data->map_height)
	{
		x = 0;
		while (x < data->map_width)
		{
			if (y == 0 || y == data->map_height - 1 || x == 0
				|| x == data->map_width - 1)
			{
				if (data->map2d[y][x] != '1')
					return (0);
			}
			else if (y >= data->map_height || x >= data->map_width
				|| !data->map2d[y])
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

// Check if the player position is valid
int	check_player_position(t_data *data, int y, int x, int *player_count)
{
	if (data->map2d[y][x] == 'P')
	{
		(*player_count)++;
		if (*player_count > 1)
			return (0);
		if (y != data->player_y_position || x != data->player_x_position)
			return (0);
	}
	return (1);
}

// Validate the player position
int	validate_player_position(t_data *data)
{
	int	player_count;
	int	y;
	int	x;

	player_count = 0;
	y = 0;
	while (y < data->map_height)
	{
		x = 0;
		while (x < data->map_width)
		{
			if (!check_player_position(data, y, x, &player_count))
				return (0);
			x++;
		}
		y++;
	}
	return (player_count == 1);
}
