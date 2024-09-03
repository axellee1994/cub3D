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
	new->win = win;
	new->h = 0;
	new->w = 0;
	new->img_ = mlx_xpm_file_to_image(mlx->mlx, tex_file,
			&(new->w), &(new->h));
	if (!new->img)
	{
		free(new);
		return (NULL);
	}
	new->addr = mlx_get_data_addr(img->img,
			&(new->bpp), &(new->line_len), &(new->endian));
//	new->next = NULL;
//	new->update_time = 0;
	return (new);
}

int	load_wall_texture(t_mlx *mlx, t_scene *scene)
{
	mlx->dt->north = new_texture(mlx, scene->north);
	if (!(mlx->dt->north))
		ft_printf("Error\nFailed to load north texture\n");
	mlx->dt->south = new_texture(mlx, scene->south);
	if (!(mlx->dt->south))
		ft_printf("Error\nFailed to load south texture\n");
	mlx->dt->east = new_texture(mlx, scene->east);
	if (!(mlx->dt->east))
		ft_printf("Error\nFailed to load east texture\n");
	mlx->dt->west = new_texture(mlx, scene->west);
	if (!(mlx->dt->west))
		ft_printf("Error\nFailed to load west texture\n");
	if (!(mlx->dt->north) || !(mlx->dt->south) || !(mlx->dt->east) || !(mlx->dt->west))
		return (0);
	return (1);

}

void	init_textures(t_mlx *mlx, t_scene *scene)
{
/*	t_info	*info;

	info = ft_calloc(1, sizeof(t_info));
	if (!info)
	{
		ft_putstr_fd("Error\nMemory allocation failed: info\n", STDERR_FILENO);
		return (NULL);
	}*/
	mlx->dt->floor = convert_rgb(ft_atoi(scene->floor[0]),
					ft_atoi(scene->floor[1]), ft_atoi(scene->floor[2]));
	mlx->dt->ceiling = convert_rgb(ft_atoi(scene->ceiling[0]),
					ft_atoi(scene->ceiling[1]), ft_atoi(scene->ceiling[2]));
	if (!(data->floor) || !(data->ceiling))//can this even be detected?
	{	
		ft_putstr_fd("Error\nColor conversion failed: floor/ceiling\n", STDERR_FILENO);
//		return (NULL);
	}
	load_wall_texture(mlx, scene);
//		return (NULL);
//	return (info);
}
