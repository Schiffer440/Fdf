/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adugain <adugain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 11:30:37 by adugain           #+#    #+#             */
/*   Updated: 2023/07/22 11:56:09 by adugain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	t_fdf	**matrix;

	if (argc != 2)
		ft_error("usage: ./fdf map.fdf");
	matrix = read_map(*++argv);
	init_param((*matrix));
	draw(matrix);
	mlx_hook((*matrix)->win, \
	ClientMessage, StructureNotifyMask, handle_message, matrix);
	mlx_key_hook((*matrix)->win, deal_key, matrix);
	mlx_loop((*matrix)->mlx);
}
