/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:12:57 by axlee             #+#    #+#             */
/*   Updated: 2024/09/28 13:28:25 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	get_step_direction(int start, int end)
{
	if (start < end)
		return (1);
	return (-1);
}

static void	init_line_data(t_point start, t_point end, t_line_data *data)
{
	data->dx = abs(end.x - start.x);
	data->dy = -abs(end.y - start.y);
	data->sx = get_step_direction(start.x, end.x);
	data->sy = get_step_direction(start.y, end.y);
	data->err = data->dx + data->dy;
}

static void	update_line(t_point *start, t_line_data *data)
{
	int	e2;

	e2 = 2 * data->err;
	if (e2 >= data->dy)
	{
		data->err += data->dy;
		start->x += data->sx;
	}
	if (e2 <= data->dx)
	{
		data->err += data->dx;
		start->y += data->sy;
	}
}

void	draw_line(t_mlx *mlx, t_point start, t_point end, int color)
{
	t_line_data	data;

	init_line_data(start, end, &data);
	while (1)
	{
		draw_pixel(mlx, start.x, start.y, color);
		if (start.x == end.x && start.y == end.y)
			break ;
		update_line(&start, &data);
	}
}
