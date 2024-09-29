/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 20:17:43 by jolai             #+#    #+#             */
/*   Updated: 2024/09/29 22:08:29 by jolai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	get_tex_info(char *line, t_scene *det)
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
		if (i == 1 || is_empty_line(arr[1]))
			return (load_error("Missing texture file", NULL, arr, NULL), 0);
		if (i > 2)
			return (load_error("Too many texture files", NULL, arr, NULL), 0);
		if (!ft_strcmp(arr[0], "NO") && !(det->north))
			det->north = ft_strtrim(arr[1], "\n");
		else if (!ft_strcmp(arr[0], "SO") && !(det->south))
			det->south = ft_strtrim(arr[1], "\n");
		else if (!ft_strcmp(arr[0], "WE") && !(det->west))
			det->west = ft_strtrim(arr[1], "\n");
		else if (!ft_strcmp(arr[0], "EA") && !(det->east))
			det->east = ft_strtrim(arr[1], "\n");
		else
			return (load_error("Duplicate texture", NULL, arr, NULL), 0);
		ft_split_free(&arr);
		return (1);
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
			ft_putstr_fd("Error\nInvalid color format", STDERR_FILENO);
			ft_split_free(&arr);
			return (0);
		}
		if (!ft_strncmp(line, "F ", 2) && !(det->floor))
			det->floor = arr;
		else if (!ft_strncmp(line, "C ", 2) && !(det->ceiling))
			det->ceiling = arr;
		else
		{
			ft_putstr_fd("Error\nDuplicate color information", STDERR_FILENO);
			ft_split_free(&arr);
			return (0);
		}
		return (1);
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
		ft_putstr_fd("Error\nInvalid map file name.", STDERR_FILENO);
		ft_putstr_fd("File name must end in .cub\n", STDERR_FILENO);
		return (NULL);
	}
	details = ft_calloc(1, sizeof(t_scene));
	if (!details)
		return (load_error("Memory allocation failed: Scene", NULL, NULL, NULL)
			, NULL);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (load_error("Failed to open .cub file", NULL, NULL, details)
			, NULL);
	line = get_next_line(fd);
	while (line)
	{
		if (!is_empty_line(line))
		{
			if (!is_tex_info(line))
				break ;
			if (!get_tex_info(line, details))
			{
				while (line)
				{
					free(line);
					line = get_next_line(fd);
				}
				free_scene(details);
				close(fd);
				return (NULL);
			}
		}
		free(line);
		line = get_next_line(fd);
	}
	full = NULL;
	while (line)
	{
		full = ft_strjoin_free(full, line);
		free(line);
		if (!full)
		{
			load_error("Error while reading map", NULL, NULL, details);
			close(fd);
			return (NULL);
		}
		line = get_next_line(fd);
	}
	if (!(details->north) || !(details->south) || !(details->east)
		|| !(details->west) || !(details->floor) || !(details->ceiling))
	{
		load_error("Invalid/Missing texture information", full, NULL, details);
		close(fd);
		return (NULL);
	}
	if (ft_strnstr(full, "\n\n", ft_strlen(full)))
	{
		load_error("Empty line detected in map", full, NULL, details);
		close(fd);
		return (NULL);
	}
	if (!valid_map_elem(full) || !valid_num_player_pos(full))
	{
		load_error(NULL, full, NULL, details);
		close(fd);
		return (NULL);
	}
	details->map = ft_split(full, '\n');
	free(full);
	close(fd);
	return (details);
}
