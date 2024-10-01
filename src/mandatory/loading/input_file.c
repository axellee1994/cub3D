/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 20:17:43 by jolai             #+#    #+#             */
/*   Updated: 2024/09/30 17:21:59 by jolai            ###   ########.fr       */
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
	load_error("Invalid number of player starting position", NULL, NULL, NULL);
	return (0);
}

int	read_map(int fd, char *line, t_scene *scene)
{
	char	*full;

	full = NULL;
	while (line)
	{
		full = ft_strjoin_free(full, line);
		free(line);
		if (!full)
			return (load_error("Error while reading map", NULL, NULL, scene),
				0);
		line = get_next_line(fd);
	}
	if (!(scene->north) || !(scene->south) || !(scene->east)
		|| !(scene->west) || !(scene->floor) || !(scene->ceiling))
		return (load_error("Missing texture information", full, NULL, scene),
			0);
	if (ft_strnstr(full, "\n\n", ft_strlen(full)))
		return (load_error("Empty line detected in map", full, NULL, scene), 0);
	if (!valid_map_elem(full) || !valid_num_player_pos(full))
		return (load_error(NULL, full, NULL, scene), 0);
	scene->map = ft_split(full, '\n');
	free(full);
	return (1);
}

int	read_details(int fd, t_scene *scene)
{
	char	*line;

	line = read_texture(fd, &scene);
	if (!scene)
		return (0);
	if (!line)
	{
		close(fd);
		return (load_error("Missing map", NULL, NULL, scene), 0);
	}
	if (!read_map(fd, line, scene))
	{
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}

t_scene	*read_cub_file(char *file)
{
	int		fd;
	t_scene	*scene;

	if (ft_strncmp(&file[ft_strlen(file) - 4], ".cub", 4) != 0)
	{
		ft_putstr_fd("Error\nInvalid map file name.", STDERR_FILENO);
		ft_putstr_fd("File name must end in .cub\n", STDERR_FILENO);
		return (NULL);
	}
	scene = ft_calloc(1, sizeof(t_scene));
	if (!scene)
		return (load_error("Memory allocation failed: Scene", NULL, NULL, NULL)
			, NULL);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (load_error("Failed to open .cub file", NULL, NULL, scene)
			, NULL);
	if (!read_details(fd, scene))
		return (NULL);
	return (scene);
}
