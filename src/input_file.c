/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolai <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 20:17:43 by jolai             #+#    #+#             */
/*   Updated: 2024/08/19 21:46:21 by jolai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	*ft_strremove(char *str, char c)
{
	char	*new;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(str);
	while (str[i])
	{
		if (str[i] == c)
			len--;
		i++;
	}
	new = malloc(len * sizeof(char));
	len = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != c)
			new[len] = str[i];
		if (str[i] != c)
			len++;
		i++;
	}
	free (str);
	return (new);
}

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
	if (det->north)
		free (det->north);
	if (det->south)
		free (det->south);
	if (det->west)
		free (det->west);
	if (det->east)
		free (det->east);
	if (det->floor)
		free (det->floor);
	if (det->ceiling)
		free (det->ceiling);
	if (det->map)
		ft_split_free(&(det->map));
}

void	get_tex_info(char *line, t_scene *det)//account for duplicate texture
{
	char	**arr;
	int		i;

	arr = ft_split(line, ' ');
	i = 0;
	while (arr[i])
		i++;
	if (i > 2)
	{
		ft_putstr_fd("Invalid texture format\n", 2);
		ft_split_free(&arr);
		return ;
	}
	if (!ft_strcmp(arr[0], "NO") && i == 2)
		det->north = ft_strdup(arr[1]);
	if (!ft_strcmp(arr[0], "SO") && i == 2)
		det->south = ft_strdup(arr[1]);
	if (!ft_strcmp(arr[0], "WE") && i == 2)
		det->west = ft_strdup(arr[1]);
	if (!ft_strcmp(arr[0], "EA") && i == 2)
		det->east = ft_strdup(arr[1]);
	if (!ft_strcmp(arr[0], "F"))
		det->floor = ft_strdup(arr[1]);
	if (!ft_strcmp(arr[0], "C"))
		det->ceiling = ft_strdup(arr[1]);
	ft_split_free(&arr);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*new;

	if (!s1)
		new = ft_strdup(s2);
	else
	{
		new = ft_strjoin(s1, s2);
		free (s1);
	}
	return (new);
}

t_scene	*check_cub_file(char *file)
{
	int		fd;
	char	*line;
	t_scene	*details;
	char	**test;
	char	*full;
	int		i;

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
		ft_putstr_fd("Failed to open .cub file\n", STDERR_FILENO);
		return (NULL);	
	}
	details = ft_calloc(1, sizeof(t_scene));
	if (!details)
	{
		ft_putstr_fd("Memory allocation failed: Scene details\n", STDERR_FILENO);
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
		free (line);
		line = get_next_line(fd);
		if (details->north && details->south && details->east && details->west
			&& details->floor && details->ceiling)
			break ;
	}
	full = NULL;
	while (line)
	{
		full = ft_strjoin_free(full, line);
		free (line);
		line = get_next_line(fd);
	}
	test = ft_split(full, '\n');
	free(full);
	i = 0;
	while (test[i])
	{
		printf("Line: %s\n", test[i]);
		i++;
	}
	i = 0;
	while (test[i])
	{
		free(test[i]);
		i++;
	}
	free(test);
	close(fd);
	return (details);
}

	
/*
void	read_cub_file(char *file)
{
	int		fd;
	char	*line;
	char	**test;
	char	*full;
	int		i;

	if (ft_strncmp(&file[ft_strlen(file) - 4], ".cub", 4) != 0)
	{
		printf("Error\nInvalid map file name: %s\n", file);
		printf("File name must end in .cub\n");
		return ;
	}
	fd = open(file, O_RDONLY);
	full = NULL;
	line = get_next_line(fd);
	while (line)
	{
		full = ft_strjoin_free(full, line);
		free (line);
		line = get_next_line(fd);
	}
	test = ft_split(full, '\n');
	free(full);
	i = 0;
	while (test[i])
	{
		printf("Line: %s\n", test[i]);
		i++;
	}
	i = 0;
	while (test[i])
	{
		free(test[i]);
		i++;
	}
	free(test);
}*/

