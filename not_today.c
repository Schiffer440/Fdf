/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   not_today.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adugain <adugain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:14:58 by adugain           #+#    #+#             */
/*   Updated: 2023/05/17 16:40:28 by adugain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "squeex.h"

int	init(t_fdf *fdf)
{
	fdf->mlx.mlx = mlx_init();
		if (fdf->mlx.mlx == NULL)
			return (0);
	fdf->mlx.win = mlx_new_window(fdf->mlx.mlx, WIN_X, WIN_Y, "Fdf");
		if (fdf->mlx.win == NULL)
		{
			free(fdf->mlx.win);
			return (0);
		}
	return (1);
}

int	fdf_exit(t_fdf *fdf)
{
	// free_map(&fdf->map);
	if (fdf->mlx.mlx && fdf->mlx.win)
		mlx_destroy_window(fdf->mlx.mlx, fdf->mlx.win);
	// if (fdf->mlx.mlx && fdf->mlx.image)
	// 	mlx_destroy_image(fdf->mlx.mlx, fdf->mlx.image);
	exit(0);
	return (0);
}

int	key_hook(int keycode, t_fdf *fdf)
{
	if (keycode == XK_Escape)
		fdf_exit(fdf);
	return (0);
}

int	render(t_fdf *fdf)
{
	if (fdf->mlx.win != NULL)
		mlx_pixel_put(fdf->mlx.mlx, fdf->mlx.win, 
			WIN_X / 2, WIN_Y / 2, RED_PIXEL);
	return (0);
}

void	add_hooks(t_fdf *fdf)
{
	mlx_key_hook(fdf->mlx.win, key_hook, fdf);
	mlx_loop_hook(fdf->mlx.mlx, &render, fdf);
	mlx_hook(fdf->mlx.win, DestroyNotify, 0, fdf_exit, fdf);
}

int	main()
{
	t_fdf	fdf;
	
		if (!init(&fdf))
			return (0);
		add_hooks(&fdf);
		mlx_loop(fdf.mlx.mlx);
		free(fdf.mlx.mlx);
}