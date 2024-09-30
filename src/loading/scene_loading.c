/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_loading.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolai <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 17:17:31 by jolai             #+#    #+#             */
/*   Updated: 2024/09/30 17:21:41 by jolai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	get_tex_file(char *line, t_scene *scene)
{
	char	**arr;
	int		i;

	i = 0;
	arr = ft_split(line, ' ');
	while (arr[i])
		i++;
	if (i == 1 || is_empty_line(arr[1]))
		return (load_error("Missing texture file", NULL, arr, scene), 0);
	if (i > 2)
		return (load_error("Too many texture files", NULL, arr, scene), 0);
	if (!ft_strcmp(arr[0], "NO") && !(scene->north))
		scene->north = ft_strtrim(arr[1], "\n");
	else if (!ft_strcmp(arr[0], "SO") && !(scene->south))
		scene->south = ft_strtrim(arr[1], "\n");
	else if (!ft_strcmp(arr[0], "WE") && !(scene->west))
		scene->west = ft_strtrim(arr[1], "\n");
	else if (!ft_strcmp(arr[0], "EA") && !(scene->east))
		scene->east = ft_strtrim(arr[1], "\n");
	else
		return (load_error("Duplicate texture", NULL, arr, scene), 0);
	ft_split_free(&arr);
	return (1);
}

int	get_color_val(char *line, t_scene *scene)
{
	char	**arr;
	char	*temp;
	int		i;

	i = 0;
	arr = ft_split(&line[1], ',');
	while (arr[i])
	{
		temp = ft_strtrim(arr[i], " \n");
		free(arr[i]);
		arr[i] = temp;
		i++;
	}
	if (i != 3)
		return (load_error("Invalid color format", NULL, arr, scene), 0);
	if (!ft_strncmp(line, "F ", 2) && !(scene->floor))
		scene->floor = arr;
	else if (!ft_strncmp(line, "C ", 2) && !(scene->ceiling))
		scene->ceiling = arr;
	else
		return (load_error("Duplicate color information", NULL, arr, scene), 0);
	return (1);
}

int	get_tex_info(char *line, t_scene *scene)
{
	if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3)
		|| !ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3))
		return (get_tex_file(line, scene));
	else
		return (get_color_val(line, scene));
}

char	*read_texture(int fd, t_scene **scene)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (!is_empty_line(line))
		{
			if (!is_tex_info(line))
				break ;
			if (!get_tex_info(line, *scene))
			{
				*scene = NULL;
				while (line)
				{
					free(line);
					line = get_next_line(fd);
				}
				close(fd);
				return (NULL);
			}
		}
		free(line);
		line = get_next_line(fd);
	}
	return (line);
}
