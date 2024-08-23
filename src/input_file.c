/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolai <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 20:17:43 by jolai             #+#    #+#             */
/*   Updated: 2024/08/23 21:00:04 by jolai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
/*
char	*ft_strremove(char *str, char *set)
{
	char	*new;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(str);
	while (str[i])
	{
		if (ft_strchr(set, str[i]))
			len--;
		i++;
	}
	new = malloc((len + 1) * sizeof(char));
	len = 0;
	i = 0;
	while (str[i])
	{
		if (!ft_strchr(set, str[i]))
			new[len] = str[i];
		if (!ft_strchr(set, str[i]))
			len++;
		i++;
	}
	new[len] = '\0';
	free(str);
	return (new);
}*/

int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\f' && line[i] != '\n'
			&& line[i] != '\r' && line[i] != '\t' && line[i] != '\v')
			return (0);
		i++;
	}
	return (1);
}

int	is_tex_info(char *line)
{
	if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3)
		|| !ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3)
		|| !ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "C ", 2))
		return (1);
	return (0);
}

void	free_details(t_scene *det)
{
	if (!det)
		return ;
	if (det->north)
		free(det->north);
	if (det->south)
		free(det->south);
	if (det->west)
		free(det->west);
	if (det->east)
		free(det->east);
	if (det->floor)
		ft_split_free(&(det->floor));
	if (det->ceiling)
		ft_split_free(&(det->ceiling));
	if (det->map)
		ft_split_free(&(det->map));
	free (det);
}

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
		if (i > 3)
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

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*new;

	if (!s1)
		new = ft_strdup(s2);
	else
	{
		new = ft_strjoin(s1, s2);
		free(s1);
	}
	return (new);
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
		line = get_next_line(fd);
	}
	if (!(details->north) || !(details->south) || !(details->east) || !(details->west)
		|| !(details->floor) || !(details->ceiling))
	{
		free(full);
		ft_putstr_fd("Error\nInvalid/Missing texture information\n", STDERR_FILENO);
		free_details(details);
		return (NULL);
	}
	if (ft_strcmp(full, "\n\n"))
	{
		free(full);
		free_details(details);
		ft_putstr_fd("Error\nEmpty line detected in map\n", STDERR_FILENO);
		return (NULL);
	}
	details->map = ft_split(full, '\n');//split the map by newlines
	free(full);
	print_details(details);
	close(fd);
	return (details);
}
