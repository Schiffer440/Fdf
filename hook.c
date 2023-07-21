/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adugain <adugain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 11:51:57 by adugain           #+#    #+#             */
/*   Updated: 2023/07/21 15:51:58 by adugain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	do_key(int key, t_fdf **matrix)
{
	if (key == XK_KP_Add)
		(*matrix)->scale += 3;
	if (key == XK_KP_Subtract)
		(*matrix)->scale -= 3;
	if (key == XK_z || key == XK_w)
		(*matrix)->z_scale += 1;
	if (key == XK_s)
		(*matrix)->z_scale -= 1;
	if (key == XK_Up)
		(*matrix)->shift_y -= 10;
	if (key == XK_Down)
		(*matrix)->shift_y += 10;
	if (key == XK_Left)
		(*matrix)->shift_x -= 10;
	if (key == XK_Right)
		(*matrix)->shift_x += 10;
	// if (key == XK_i)
	// 	(*matrix)->is_isometric = ((*matrix)->is_isometric) ? 0 : 1;
	// if (key == XK_q || key == XK_a)
	// 	(*matrix)->angle += 0.05;
	// if (key == XK_d)
	// 	(*matrix)->angle -= 0.05;
}

int	handle_message(t_fdf **matrix)
{
	mlx_destroy_window((*matrix)->mlx, (*matrix)->win);
	mlx_destroy_display((*matrix)->mlx);
	free((*matrix)->mlx);
	free_matrix(matrix);
	exit(0);
	return (0);
}

int		deal_key(int key, t_fdf **matrix)
{
		mlx_clear_window((*matrix)->mlx, (*matrix)->win);
		do_key(key, matrix);
		draw(matrix);
	
	if (key == XK_Escape)
	{
		mlx_destroy_window((*matrix)->mlx, (*matrix)->win);
		mlx_destroy_display((*matrix)->mlx);
		free((*matrix)->mlx);
		free_matrix(matrix);
		exit(0);
	}
	return (0);
}
