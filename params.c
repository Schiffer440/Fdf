/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adugain <adugain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 11:43:30 by adugain           #+#    #+#             */
/*   Updated: 2023/07/21 16:51:29 by adugain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "fdf.h"

void	set_param(t_fdf *a, t_fdf *b, t_fdf *param)
{
	zoom(a, b, param);
	isometric(a, param->angle);
	isometric(b, param->angle);
	a->x += param->shift_x;
	a->y += param->shift_y;
	b->x += param->shift_x;
	b->y += param->shift_y;
}

// static int	ft_scale(t_fdf *param)
// {
// 	int	a;
// 	int	b;

// 	a = ((WIDTH * 0.10) / (param->x - 1)) / 2;
// 	b = ((HEIGHT * 0.10) / (param->y - 1)) / 2;
	
// 	if (a > b)
// 		return (a);
// 	else
// 		return (b);
// }

void	init_param(t_fdf *param)
{
	param->scale = 20;
	param->z_scale = 1;
	// param->is_isometric = 1;
	param->angle = M_PI / 3;
	param->win_x = WIDTH;
	param->win_y = HEIGHT;
	param->shift_x = param->win_x / 2;
	param->shift_y = param->win_y / 4;
	param->mlx = mlx_init();
	param->win =\
	mlx_new_window(param->mlx, param->win_x, param->win_y, "FdF");
}

void	zoom(t_fdf *a, t_fdf *b, t_fdf *param)
{
	a->x *= param->scale;
	a->y *= param->scale;
	b->x *= param->scale;
	b->y *= param->scale;
	a->z *= param->z_scale;
	b->z *= param->z_scale;
}