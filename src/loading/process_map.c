/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 21:04:26 by jolai             #+#    #+#             */
/*   Updated: 2024/10/01 01:35:04 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	get_map_dimensions(char **map, t_data *data)
{
	int	rows;
	int	cols;
	int	temp;

	rows = 0;
	cols = 0;
	temp = 0;
	while (map[rows])
	{
		temp = ft_strlen(map[rows]);
		if (temp > cols)
			cols = temp;
		rows++;
	}
	if (rows < 3 || cols < 3 || rows > 50 || cols > 50)
	{
		free_map_data(data);
		load_error("Invalid map dimensions", NULL, NULL, NULL);
		return (0);
	}
	data->map_height = rows;
	data->map_width = cols;
	return (1);
}

void	get_player_position(char **map, t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'N' || map[y][x] == 'S'
				|| map[y][x] == 'E' || map[y][x] == 'W')
			{
				data->player_y_position = y;
				data->player_x_position = x;
			}
			x++;
		}
		y++;
	}
}

void	assign_map_value(char **prev, char *line, int row, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->map_width)
	{
		line[i] = '0';
		if (((unsigned long)i <= ft_strlen(prev[row]))
			&& prev[row][i] && prev[row][i] != ' ')
		{
			line[i] = prev[row][i];
		}
		i++;
	}
	line[i] = '\0';
}

char	**convert_map(char **prev, t_data *data)
{
	char	**new;
	char	*line;
	int		i;

	new = ft_calloc(data->map_height + 1, sizeof(char *));
	if (!new)
	{
		load_error("Memory allocation error: Map", NULL, NULL, NULL);
		return (NULL);
	}
	i = 0;
	while (i < data->map_height)
	{
		line = ft_calloc(data->map_width + 1, sizeof(char));
		if (!line)
		{
			load_error("Memory allocation failed: Map line", NULL, new, NULL);
			return (NULL);
		}
		new[i] = line;
		assign_map_value(prev, line, i, data);
		i++;
	}
	return (new);
}

void	map_fill(int x, int y, t_data *data, int *valid)
{
	char	c;

	if (x < 0 || x >= data->map_width
		|| y < 0 || y >= data->map_height || !(data->map2d[y][x]))
	{
		(*valid) = 0;
		return ;
	}
	c = data->map2d[y][x];
	if (c == '1' || c == '.' || c == 'n' || c == 's' || c == 'w' || c == 'e')
		return ;
	else if (c == '0')
		data->map2d[y][x] = '.';
	else if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		data->map2d[y][x] = data->map2d[y][x] + 32;
	map_fill(x + 1, y, data, valid);
	map_fill(x - 1, y, data, valid);
	map_fill(x, y + 1, data, valid);
	map_fill(x, y - 1, data, valid);
}
