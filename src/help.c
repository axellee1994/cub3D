/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 14:26:06 by axlee             #+#    #+#             */
/*   Updated: 2024/09/29 20:13:18 by jolai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Display the help text
void	display_help(t_mlx *mlx)
{
	int	help_text_x;
	int	help_text_y;
	int	text_color;
	int	line_spacing;

	text_color = BLACK;
	line_spacing = 20;
	help_text_x = 10;
	help_text_y = SCREEN_HEIGHT - line_spacing * 9;
	mlx_string_put(mlx->mlx, mlx->win, help_text_x, help_text_y, text_color,
		"Keybindings:");
	mlx_string_put(mlx->mlx, mlx->win, help_text_x, help_text_y + line_spacing,
		text_color, "[W][A][S][D]: Move");
	mlx_string_put(mlx->mlx, mlx->win, help_text_x, help_text_y + 2
		* line_spacing, text_color, "[Left][Right]: Rotate");
	mlx_string_put(mlx->mlx, mlx->win, help_text_x, help_text_y + 3
		* line_spacing, text_color, "[ESC]: Exit game");
	mlx_string_put(mlx->mlx, mlx->win, help_text_x, help_text_y + 4
		* line_spacing, text_color, "[H]: Toggle help");
	mlx_string_put(mlx->mlx, mlx->win, help_text_x, help_text_y + 5
		* line_spacing, text_color, "[M]: Toggle mouse");
}
