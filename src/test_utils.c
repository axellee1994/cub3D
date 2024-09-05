/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolai <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 20:17:43 by jolai             #+#    #+#             */
/*   Updated: 2024/09/05 16:13:50 by jolai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	print_details(t_scene *details)
{
	int	i;

	if (!details)
		return ;
	if (details->north)
		printf("NORTH: %s\n", details->north);
	if (details->south)
		printf("SOUTH: %s\n", details->south);
	if (details->east)
		printf("EAST: %s\n", details->east);
	if (details->west)
		printf("WEST: %s\n", details->west);
	if (details->floor)
	{
		i = 0;
		while (details->floor[i])
		{
			printf("FLOOR: %s\n", details->floor[i]);
			i++;
		}
	}
	if (details->ceiling)
	{
		i = 0;
		while (details->ceiling[i])
		{
			printf("CEILING: %s\n", details->ceiling[i]);
			i++;
		}
	}
	if (details->map)
	{
		i = 0;
		while (details->map[i])
		{
			printf("Map: %s\n", details->map[i]);
			i++;
		}
	}
}
