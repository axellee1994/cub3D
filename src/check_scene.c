/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 21:28:37 by jolai             #+#    #+#             */
/*   Updated: 2024/09/27 09:12:26 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3D.h"

int	check_color_val(char **arr)
{
	int	i;
	int	j;

	i = 0;
	while (arr[i])
	{
		j = 0;
		while (arr[i][j])
		{
			if (!ft_isdigit(arr[i][j]))
				return (0);
			j++;
		}
		if (ft_atoi(arr[i]) > 255 || ft_atoi(arr[i]) < 0)
			return (0);
		i++;
	}
	return (i == 3);  // Ensure exactly 3 color components
}

int	check_tex_file(char *file)
{
	int	fd;

	if (ft_strncmp(&file[ft_strlen(file) - 4], ".xpm", 4) != 0)
	{
		ft_putstr_fd("Error\nInvalid texture file name: ", STDERR_FILENO);
		ft_putstr_fd(file, STDERR_FILENO);
		ft_putstr_fd("\nFile name must end in .xpm\n", STDERR_FILENO);
		return (0);
	}
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error\nFailed to open .xpm file: ", STDERR_FILENO);
		ft_putstr_fd(file, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		return (0);	
	}
	close(fd);
	return (1);
}

int	check_scene(t_scene *det)
{
	if (!det)
		return (0);
	if (!check_color_val(det->floor) || !check_color_val(det->ceiling))
		return (0);
	if (!check_tex_file(det->north) || !check_tex_file(det->south) || 
		!check_tex_file(det->east) || !check_tex_file(det->west))
		return (0); 
//	check map(flood fill on 0 and throw error if reach side or space?)
	return (1);
}
