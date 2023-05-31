/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adugain <adugain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 11:51:57 by adugain           #+#    #+#             */
/*   Updated: 2023/05/31 11:52:46 by adugain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	do_key(int key, t_fdf **matrix)
{
	if (key == XK_KP_Add)
		PRM.scale += 3;
	if (key == XK_KP_Subtract)
		PRM.scale -= 3;
	if (key == XK_z || key == XK_w)
		PRM.z_scale += 1;
	if (key == XK_s)
		PRM.z_scale -= 1;
	if (key == XK_Up)
		PRM.shift_y -= 10;
	if (key == XK_Down)
		PRM.shift_y += 10;
	if (key == XK_Left)
		PRM.shift_x -= 10;
	if (key == XK_Right)
		PRM.shift_x += 10;
	if (key == XK_i)
		PRM.is_isometric = (PRM.is_isometric) ? 0 : 1;
	if (key == XK_q || key == XK_a)
		PRM.angle += 0.05;
	if (key == XK_d)
		PRM.angle -= 0.05;
}

int	handle_message(t_fdf **matrix)
{
	mlx_destroy_window(PRM.mlx, PRM.win);
	free(matrix);
	exit(0);
	return (0);
}

int		deal_key(int key, t_fdf **matrix)
{
		mlx_clear_window(PRM.mlx, PRM.win);
		do_key(key, matrix);
		draw(matrix);
	
	if (key == XK_Escape)
	{
		mlx_destroy_window(PRM.mlx, PRM.win);
		free(matrix);
		exit(0);
	}
	return (0);
}
