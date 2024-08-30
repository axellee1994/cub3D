#include "cub3D.h"

unsigned int	convert_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

t_img	*new_texture(t_win *win, char *tex_file)
{
	t_img	*new;

	new = (t_img *)malloc(sizeof(t_img));
	if (!new)
		return (NULL);
	new->win = win;
	new->h = 0;
	new->w = 0;
	new->img_ = mlx_xpm_file_to_image(win->mlx_ptr, tex_file,
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

int	load_wall_texture(t_scene *scene, t_info *info, t_mlx *data)
{
	info->north = new_sprite(data->win, scene->north);
	if (!(info->north))
		ft_printf("Error\nFailed to load north texture\n");
	info->south = new_sprite(data->win, scene->south);
	if (!(info->south))
		ft_printf("Error\nFailed to load south texture\n");
	info->east = new_sprite(data->win, scene->east);
	if (!(info->east))
		ft_printf("Error\nFailed to load east texture\n");
	info->west = new_sprite(data->win, scene->west);
	if (!(info->west))
		ft_printf("Error\nFailed to load west texture\n");
	if (!(info->north) || !(info->south) || !(info->east) || !(info->west))
		return (0);
	return (1);

}

t_info	load_texture(t_scene *scene)
{
	t_info	*info;

	info = ft_calloc(1, sizeof(t_info));
	if (!info)
	{
		ft_putstr_fd("Error\nMemory allocation failed: info\n", STDERR_FILENO);
		return (NULL);
	}
	info->floor = convert_rgb(ft_atoi(scene->floor[0]),
					ft_atoi(scene->floor[1]), ft_atoi(scene->floor[2]));
	info->ceiling = convert_rgb(ft_atoi(scene->ceiling[0]),
					ft_atoi(scene->ceiling[1]), ft_atoi(scene->ceiling[2]));
	if (!(info->floor) || !(info->ceiling))
	{	
		ft_putstr_fd("Error\nColor conversion failed: floor/ceiling\n", STDERR_FILENO);
		return (NULL);
	}
	if (!load_wall_texture(scene, info, data))
		return (NULL);
	return (info);
}
