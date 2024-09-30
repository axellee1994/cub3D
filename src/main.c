/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:12:01 by axlee             #+#    #+#             */
/*   Updated: 2024/09/30 19:54:44 by jolai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_data	*process_map(t_scene *scene)
{
	t_data	*data;
	int		valid;

	valid = 1;
	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		return (load_error("Memory allocation failed: Data", NULL, NULL, NULL),
			NULL);
	if (!get_map_dimensions(scene->map, data))
		return (NULL);
	data->map2d = convert_map(scene->map, data);
	if (!(data->map2d))
	{
		free_map_data(data);
		return (NULL);
	}
	get_player_position(data->map2d, data);
	map_fill(data->player_x_position, data->player_y_position, data, &valid);
	if (!valid)
	{
		free_map_data(data);
		load_error("Invalid map borders", NULL, NULL, NULL);
		return (NULL);
	}
	return (data);
}

int	check_and_initialize(int argc, char **argv, t_data **data, t_scene **scene)
{
	if (argc != 2)
	{
		ft_putstr_fd("Error: Usage: ./cub3D <map_file.cub>\n", STDERR_FILENO);
		return (0);
	}
	ft_putstr_fd("Loading map from file: ", 1);
	ft_putstr_fd(argv[1], 1);
	ft_putstr_fd("\n", 1);
	*scene = read_cub_file(argv[1]);
	if (!check_scene(*scene))
	{
		free_scene(*scene);
		return (0);
	}
	*data = process_map(*scene);
	if (!(*data))
	{
		free_scene(*scene);
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	*data;
	t_scene	*scene;

	if (!check_and_initialize(argc, argv, &data, &scene))
		return (1);
	start_the_game(data, scene);
	return (0);
}
