/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:45:17 by jolai             #+#    #+#             */
/*   Updated: 2024/09/30 17:38:57 by jolai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

unsigned int	convert_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

t_img	*new_texture(t_mlx *mlx, char *tex_file)
{
	t_img	*new;

	new = (t_img *)malloc(sizeof(t_img));
	if (!new)
		return (NULL);
	new->h = 0;
	new->w = 0;
	new->img = mlx_xpm_file_to_image(mlx->mlx, tex_file, &(new->w), &(new->h));
	if (!new->img)
	{
		free(new);
		return (NULL);
	}
	new->addr = mlx_get_data_addr(new->img, &(new->bits_per_pixel),
			&(new->line_length), &(new->endian));
	if (!new->addr)
	{
		mlx_destroy_image(mlx->mlx, new->img);
		free(new);
		return (NULL);
	}
	return (new);
}

int	init_single_texture(t_mlx *mlx, t_img **texture, char *file,
		char *direction)
{
	char	*msg;
	int		result;

	msg = ft_strjoin("Loading ", direction);
	mlx_string_put(mlx->mlx, mlx->win, 960, 540, AQUA, msg);
	free(msg);
	*texture = new_texture(mlx, file);
	if (!(*texture))
	{
		ft_putstr_fd("Error\nFailed to load ", STDERR_FILENO);
		ft_putstr_fd(direction, STDERR_FILENO);
		ft_putstr_fd(" texture\n", STDERR_FILENO);
		result = 0;
	}
	else
		result = 1;
	mlx_clear_window(mlx->mlx, mlx->win);
	return (result);
}

int	init_wall_texture(t_mlx *mlx, t_scene *scene)
{
	if (!init_single_texture(mlx, &mlx->dt->north, scene->north,
			"North Texture") || !init_single_texture(mlx, &mlx->dt->south,
			scene->south, "South Texture") || !init_single_texture(mlx,
			&mlx->dt->east, scene->east, "East Texture")
		|| !init_single_texture(mlx, &mlx->dt->west, scene->west,
			"West Texture"))
	{
		return (0);
	}
	return (1);
}

void	init_textures(t_mlx *mlx, t_scene *scene)
{
	mlx->dt->floor = convert_rgb(ft_atoi(scene->floor[0]),
			ft_atoi(scene->floor[1]), ft_atoi(scene->floor[2]));
	mlx->dt->ceiling = convert_rgb(ft_atoi(scene->ceiling[0]),
			ft_atoi(scene->ceiling[1]), ft_atoi(scene->ceiling[2]));
	if (!(mlx->dt->floor) || !(mlx->dt->ceiling))
	{
		ft_putstr_fd("Error\nColor conversion failed: floor/ceiling\n",
			STDERR_FILENO);
		free_scene(scene);
		free_and_exit(mlx);
	}
	if (!init_wall_texture(mlx, scene))
	{
		free_scene(scene);
		free_and_exit(mlx);
	}
	free_scene(scene);
}
