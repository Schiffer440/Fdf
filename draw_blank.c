/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_blank.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adugain <adugain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 11:45:09 by adugain           #+#    #+#             */
/*   Updated: 2023/07/26 18:17:57 by adugain          ###   ########.fr       */
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

static void	put_pixel(t_fdf **param, float x, float y)
{
	char	*pxl_addr;

	if (x > WIDTH || y > HEIGHT)
		return ;
	pxl_addr = (*param)->addr + \
	((int)y * (*param)->size_line + (int)x * ((*param)->bpp / 8));
	*(unsigned int *)pxl_addr = 0x00000;
}

static void	draw_line(t_fdf a, t_fdf b, t_fdf **param)
{
	float	step_x;
	float	step_y;
	float	max;
	int		color;

	set_param(&a, &b, (*param));
	step_x = b.x - a.x;
	step_y = b.y - a.y;
	max = ft_max(ft_fabs(step_x), ft_fabs(step_y));
	step_x /= max;
	step_y /= max;
	color = ft_color((b.z || a.z));
	while ((int)(a.x - b.x) || (int)(a.y - b.y))
	{
		put_pixel(param, a.x, a.y);
		a.x += step_x;
		a.y += step_y;
		// if (a.x > (*param)->win_x \
		// || a.y > (*param)->win_y || a.y < 0 || a.x < 0)
		// 	break ;
	}
}

void	draw2(t_fdf **matrix)
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
				draw_line(matrix[y][x], matrix[y + 1][x], matrix);
			}
			if (!matrix[y][x].is_last)
			{
				draw_line(matrix[y][x], matrix[y][x + 1], matrix);
			}
			if (matrix[y][x].is_last)
				break ;
			x++;
		}
		y++;
	}
	mlx_put_image_to_window((*matrix)->mlx, (*matrix)->win, \
	(*matrix)->img, 0, 0);
}
