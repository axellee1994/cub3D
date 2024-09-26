/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_elem_checks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolai <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 21:04:26 by jolai             #+#    #+#             */
/*   Updated: 2024/09/05 16:18:24 by jolai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	valid_map_elem(char *map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (map[i] != '0' && map[i] != '1'
			&& map[i] != ' ' && map[i] != '\n'
			&& map[i] != 'N' && map[i] != 'S'
			&& map[i] != 'E' && map[i] != 'W')
		{
			ft_putstr_fd("Error\nInvalid map character: ", STDERR_FILENO);
			ft_putchar_fd(map[i], STDERR_FILENO);
			ft_putstr_fd("\n", STDERR_FILENO);
			return (0);
		}
		i++;
	}
	return (1);
}

int	valid_num_player_pos(char *map)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (map[i])
	{
		if (map[i] == 'N' || map[i] == 'S' || map[i] == 'E' || map[i] == 'W')
			count++;
		i++;
	}
	if (count == 1)
		return (1);
	ft_putstr_fd("Error\nInvalid number of player starting position\n", STDERR_FILENO);
	return (0);
}

void	get_map_dimensions(char **map, t_data *data)
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
	data->map_height = rows;
	data->map_width = cols;
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

char	**convert_map(char **prev, t_data *data)
{
	char	**new;
	char	*line;
	int		i;
	int		j;

	new = ft_calloc(data->map_height + 1, sizeof(char *));
	if (!new)
	{
		ft_putstr_fd("Error\nMemory allocation error\n", STDERR_FILENO);
		return (NULL);
	}
	i = 0;
	while (i < data->map_height)
	{
		line = ft_calloc(data->map_width + 1, sizeof(char));
		if (!line)
		{
			ft_putstr_fd("Error\nMemory allocation failed\n", STDERR_FILENO);
			ft_split_free(&new);
			return (NULL);
		}
		new[i] = line;
		j = 0;
		while (j < data->map_width)
		{
			line[j] = '0';
			if (((unsigned long)j <= ft_strlen(prev[i])) && prev[i][j] && prev[i][j] != ' ')
			{
				line[j] = prev[i][j];
			}
			j++;
		}
		line[j] = '\0';
		i++;
	}
	return (new);
}

void	print_data(t_data *dt)
{
	int	i;

	i = 0;
	printf("Map size(x,y): %d, %d\n", dt->map_width, dt->map_height);
	while (dt->map2d[i])
	{
		printf("%s\n", dt->map2d[i]);
		i++;
	}
	printf("Player start(x,y): %d, %d\n", dt->player_x_position, dt->player_y_position);
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


t_data	*process_map(t_scene *scene)
{
	t_data	*data;
	int		valid;

	valid = 1;
	data = ft_calloc(1, sizeof(t_data));
	get_map_dimensions(scene->map, data);
	if (data->map_width <= 0 || data->map_height <= 0)
	{
		ft_putstr_fd("Error\nInvalid map dimensions!\n", STDERR_FILENO);
		free_map_data(data);
		return (NULL);
	}
	data->map2d = convert_map(scene->map, data);
	get_player_position(data->map2d, data);
//	print_data(data);
	map_fill(data->player_x_position, data->player_y_position, data, &valid);
//	print_data(data);
	if (!valid)
	{
		ft_putstr_fd("Error\nInvalid map borders!\n", STDERR_FILENO);
		free_map_data(data);
		return (NULL);
	}
	print_data(data);
	return (data);
}
