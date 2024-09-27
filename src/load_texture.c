/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:45:17 by jolai             #+#    #+#             */
/*   Updated: 2024/09/27 09:19:19 by axlee            ###   ########.fr       */
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

int	load_wall_texture(t_mlx *mlx, t_scene *scene)
{
	if (!load_single_texture(mlx, &mlx->dt->north, scene->north,
			"North Texture") || !load_single_texture(mlx, &mlx->dt->south,
			scene->south, "South Texture") || !load_single_texture(mlx,
			&mlx->dt->east, scene->east, "East Texture")
		|| !load_single_texture(mlx, &mlx->dt->west, scene->west,
			"West Texture"))
	{
		return (0);
	}
	return (1);
}

int	load_single_texture(t_mlx *mlx, t_img **texture, char *file,
		char *direction)
{
	char	*loading_message;
	int		result;

	loading_message = ft_strjoin("Loading ", direction);
	mlx_string_put(mlx->mlx, mlx->win, 960, 540, 0x00FFFF, loading_message);
	free(loading_message); // Free the allocated string
	*texture = new_texture(mlx, file);
	if (!(*texture))
	{
		ft_putstr_fd("Error\nFailed to load ", STDERR_FILENO);
		ft_putstr_fd(direction, STDERR_FILENO);
		ft_putstr_fd(" texture\n", STDERR_FILENO);
		result = 0;
	}
	else
	{
		result = 1;
	}
	mlx_clear_window(mlx->mlx, mlx->win);
	return (result);
}

void	init_textures(t_mlx *mlx, t_scene *scene)
{
	/*	t_info	*info;
		info = ft_calloc(1, sizeof(t_info));
		if (!info)
		{
			ft_putstr_fd("Error\nMemory allocation failed: info\n",
				STDERR_FILENO);
			return (NULL);
		}*/
	mlx->dt->floor = convert_rgb(ft_atoi(scene->floor[0]),
			ft_atoi(scene->floor[1]), ft_atoi(scene->floor[2]));
	mlx->dt->ceiling = convert_rgb(ft_atoi(scene->ceiling[0]),
			ft_atoi(scene->ceiling[1]), ft_atoi(scene->ceiling[2]));
	if (!(mlx->dt->floor) || !(mlx->dt->ceiling)) // can this even be detected?
	{
		ft_putstr_fd("Error\nColor conversion failed: floor/ceiling\n",
			STDERR_FILENO);
		//		return (NULL);
	}
	load_wall_texture(mlx, scene);
	//		return (NULL);
	//	return (info);
}
