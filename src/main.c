/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:12:01 by axlee             #+#    #+#             */
/*   Updated: 2024/08/27 17:12:47 by jolai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Need to write a better init_argument that will be based on the .cub file
t_data	*init_argument(char *map_file)
{
	t_data	*dt;
	t_scene	*scene;

/*	dt = ft_calloc(1, sizeof(t_data));
	if (!dt)
	{
		ft_putstr_fd("Error: Memory allocation failed\n", 2);
		return (NULL);
	}*/
	ft_putstr_fd("Loading map from file: ", 1);
	ft_putstr_fd(map_file, 1);
	ft_putstr_fd("\n", 1);
	// TODO: Implement map loading from file
	scene = read_cub_file(map_file);
	if (!check_scene(scene))
	{
		free_details(scene);
		return (NULL);
	}
	dt = process_map(scene);
	free_details(scene);
	if (!dt)
		return (NULL);
/*	// Temporary hardcoded map (to be replaced with file loading)
	dt->map2d = calloc(10, sizeof(char *));
	dt->map2d[0] = strdup("1111111111111111111111111");
	dt->map2d[1] = strdup("1000000000000000000100001");
	dt->map2d[2] = strdup("1001000000000P00000000001");
	dt->map2d[3] = strdup("1001000000000000001000001");
	dt->map2d[4] = strdup("1001000000000000001000001");
	dt->map2d[5] = strdup("1001000000100000001000001");
	dt->map2d[6] = strdup("1001000000000000001000001");
	dt->map2d[7] = strdup("1001000000001000001000001");
	dt->map2d[8] = strdup("1111111111111111111111111");
	dt->map2d[9] = NULL;
	dt->player_y_position = 2;
	dt->player_x_position = 13;
	dt->map_width = 25;
	dt->map_height = 9;*/
	return (dt);
}

int	check_and_initialize(int argc, char **argv, t_data **data)
{
	if (argc != 2)
	{
		ft_putstr_fd("Error: Usage: ./cub3D <map_file.cub>\n", 2);
		return (0);
	}
	*data = init_argument(argv[1]);
	if (!*data)
	{
		ft_putstr_fd("Error: Failed to initialize data\n", 2);
		return (0);
	}
/*	if (!validate_map(*data))
	{
		ft_putstr_fd("Error: Invalid map\n", 2);
		free_map_data(*data);
		return (0);
	}
	if (!validate_player_position(*data))
	{
		ft_putstr_fd("Error: Invalid player position\n", 2);
		free_map_data(*data);
		return (0);
	}*/
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (!check_and_initialize(argc, argv, &data))
		return (1);
	start_the_game(data);
	free_map_data(data);
	return (0);
}
