/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 20:17:43 by jolai             #+#    #+#             */
/*   Updated: 2024/09/28 21:06:43 by jolai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	get_tex_info(char *line, t_scene *det)//account for duplicate texture
{
	char	**arr;
	char	*temp;
	int		i;

	i = 0;
	if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3)
		|| !ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3))
	{
		arr = ft_split(line, ' ');
		while (arr[i])
			i++;
		if (i == 1)
		{
			ft_putstr_fd("Error\nNo texture file provided\n", STDERR_FILENO);
			ft_split_free(&arr);
			return (1);
		}
		if (i > 2)
		{
			ft_putstr_fd("Error\nInvalid texture format\n", STDERR_FILENO);
			ft_split_free(&arr);
			return (1);
		}
		if (!ft_strcmp(arr[0], "NO") && !(det->north))
			det->north = ft_strtrim(arr[1], "\n");
		else if (!ft_strcmp(arr[0], "SO") && !(det->south))
			det->south = ft_strtrim(arr[1], "\n");
		else if (!ft_strcmp(arr[0], "WE") && !(det->west))
			det->west = ft_strtrim(arr[1], "\n");
		else if (!ft_strcmp(arr[0], "EA") && !(det->east))
			det->east = ft_strtrim(arr[1], "\n");
		else
		{
			ft_putstr_fd("Error\nDuplicate texture information\n", STDERR_FILENO);
			ft_split_free(&arr);
			return (1);
		}
		ft_split_free(&arr);
		return (0);
	}
	else
	{
		arr = ft_split(&line[1], ',');
		while (arr[i])
		{
			temp = ft_strtrim(arr[i], " \n");
			free(arr[i]);
			arr[i] = temp;
			i++;
		}
		if (i != 3)
		{
			ft_putstr_fd("Error\nInvalid color format\n", STDERR_FILENO);
			ft_split_free(&arr);
			return (1);
		}
		if (!ft_strncmp(line, "F ", 2) && !(det->floor))
			det->floor = arr;
		else if (!ft_strncmp(line, "C ", 2) && !(det->ceiling))
			det->ceiling = arr;
		else
		{
			ft_putstr_fd("Error\nDuplicate color information\n", STDERR_FILENO);
			ft_split_free(&arr);
			return (1);
		}
		return (0);
	}
}

t_scene	*read_cub_file(char *file)
{
	int		fd;
	char	*line;
	t_scene	*details;
	char	*full;

	if (ft_strncmp(&file[ft_strlen(file) - 4], ".cub", 4) != 0)
	{
		ft_putstr_fd("Error\nInvalid map file name:", STDERR_FILENO);
		ft_putstr_fd(file, STDERR_FILENO);
		ft_putstr_fd("File name must end in .cub\n", STDERR_FILENO);
		return (NULL);
	}
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error\nFailed to open .cub file\n", STDERR_FILENO);
		return (NULL);
	}
	details = ft_calloc(1, sizeof(t_scene));
	if (!details)
	{
		ft_putstr_fd("Error\nMemory allocation failed: Scene details\n", STDERR_FILENO);
		close(fd);
		return (NULL);
	}
	line = get_next_line(fd);
	while (line)
	{
		if (!is_empty_line(line))
		{
			if (!is_tex_info(line))
				break ;
			get_tex_info(line, details);
		}
		free(line);
		line = get_next_line(fd);
	}
	full = NULL;
	while (line)//get the whole map into one string
	{
		full = ft_strjoin_free(full, line);
		free(line);
		if (!full)
		{
			ft_putstr_fd("Error\nIssue encountered while reading map\n", STDERR_FILENO);
			free_scene(details);
			return (NULL);
		}
		line = get_next_line(fd);
	}
	if (!(details->north) || !(details->south) || !(details->east) || !(details->west)
		|| !(details->floor) || !(details->ceiling))//check for missing info
	{
		free(full);
		ft_putstr_fd("Error\nInvalid/Missing texture information\n", STDERR_FILENO);
		free_scene(details);
		return (NULL);
	}
	if (ft_strnstr(full, "\n\n", ft_strlen(full)))//check for empty line
	{
		free(full);
		free_scene(details);
		ft_putstr_fd("Error\nEmpty line detected in map\n", STDERR_FILENO);
		return (NULL);
	}
	if (!valid_map_elem(full) || !valid_num_player_pos(full))
	{
		free(full);
		free_scene(details);
		return (NULL);
	}
	details->map = ft_split(full, '\n');//split the map by newlines
	free(full);
//	print_details(details);
	close(fd);
	return (details);
}
