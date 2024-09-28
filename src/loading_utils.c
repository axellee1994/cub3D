/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 17:26:15 by jolai             #+#    #+#             */
/*   Updated: 2024/09/28 23:00:36 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

void	free_scene(t_scene *scene)
{
	if (!scene)
		return ;
	if (scene->north)
		free(scene->north);
	if (scene->south)
		free(scene->south);
	if (scene->west)
		free(scene->west);
	if (scene->east)
		free(scene->east);
	if (scene->floor)
		ft_split_free(&(scene->floor));
	if (scene->ceiling)
		ft_split_free(&(scene->ceiling));
	if (scene->map)
		ft_split_free(&(scene->map));
	free (scene);
}

void	load_error(char *msg, char *line, char **arr, t_scene *scene)
{
	if (msg)
	{
		ft_putstr_fd("Error\n", STDERR_FILENO);
		ft_putstr_fd(msg, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	if (line)
		free(line);
	if (arr)
		ft_split_free(&arr);
	if (scene)
		free_scene(scene);
}
