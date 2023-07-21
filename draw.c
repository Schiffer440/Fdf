/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adugain <adugain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 11:45:09 by adugain           #+#    #+#             */
/*   Updated: 2023/07/21 16:46:08 by adugain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	ft_color(float z)
{
	if (z > 0)
		return (0x0000ff);
	else if (z > 5)
		return (0xff0000);
	else
		return (0xffffff);
}

static void	draw_line(t_fdf a, t_fdf b, t_fdf *param)
{
	float	step_x;
	float	step_y;
	float	max;
	int		color;

	set_param(&a, &b, param);
	step_x = b.x - a.x;
	step_y = b.y - a.y;
	max = MAX(f_abs(step_x), f_abs(step_y));
	step_x /= max;
	step_y /= max;
	color = ft_color((b.z || a.z));
	while ((int)(a.x - b.x) || (int)(a.y - b.y))
	{
		mlx_pixel_put(param->mlx, param->win, a.x, a.y, color);
		a.x += step_x;
		a.y += step_y;
		if (a.x > param->win_x || a.y > param->win_y || a.y < 0 || a.x < 0)
			break ;
	}
}

void	draw(t_fdf **matrix)
{
	int		y;
	int		x;

	y = 0;
	while (matrix[y])
	{
		x = 0;
		while (1)
		{
			if (matrix[y + 1])
			{
				draw_line(matrix[y][x], matrix[y + 1][x], (*matrix));
			}
			if (!matrix[y][x].is_last)
			{
				draw_line(matrix[y][x], matrix[y][x + 1], (*matrix));
			}
				
			if (matrix[y][x].is_last)
				break ;
			x++;
		}
		y++;
	}
}