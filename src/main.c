/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:12:01 by axlee             #+#    #+#             */
/*   Updated: 2024/09/05 16:13:37 by jolai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_and_initialize(int argc, char **argv, t_data **data, t_scene **scene)
{
	if (argc != 2)
	{
		ft_putstr_fd("Error: Usage: ./cub3D <map_file.cub>\n", 2);
		return (0);
	}
	ft_putstr_fd("Loading map from file: ", 1);
	ft_putstr_fd(argv[1], 1);
	ft_putstr_fd("\n", 1);
	*scene = read_cub_file(argv[1]);
	if (!check_scene(*scene))
	{
		free_details(*scene);
		return (0);
	}
	*data = process_map(*scene);
	if (!data)
		return (0);
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
