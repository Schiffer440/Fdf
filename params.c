/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adugain <adugain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 11:43:30 by adugain           #+#    #+#             */
/*   Updated: 2023/07/26 18:10:51 by adugain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_param(t_fdf *a, t_fdf *b, t_fdf *param)
{
	zoom(a, b, param);
	if (param->is_isometric == 1)
	{
		isometric(a, param->angle);
		isometric(b, param->angle);
	}
	a->x += param->shift_x;
	a->y += param->shift_y;
	b->x += param->shift_x;
	b->y += param->shift_y;
}

void	init_mlx(t_fdf	*mlx)
{
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		ft_perror("win fail");
	mlx->win = \
	mlx_new_window(mlx->mlx, mlx->win_x, mlx->win_y, "FdF");
	if (!mlx->win)
	{	
		free(mlx->mlx);
		ft_perror("win fail");
	}
	mlx->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	if (!mlx->img)
	{
		free(mlx->mlx);
		free(mlx->win);
		ft_perror("mlx fail");
	}
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bpp, \
	&mlx->size_line, &mlx->endian);
}

void	init_param(t_fdf *param)
{
	param->scale = 20;
	param->z_scale = 1;
	param->is_isometric = 1;
	param->angle = M_PI / 3;
	param->win_x = WIDTH;
	param->win_y = HEIGHT;
	param->shift_x = param->win_x / 2;
	param->shift_y = param->win_y / 4;
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
