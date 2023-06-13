/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adugain <adugain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 11:30:37 by adugain           #+#    #+#             */
/*   Updated: 2023/06/13 11:07:24 by adugain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		main(int argc, char **argv)
{
	t_fdf	**matrix;

	if (argc != 2)
		ft_error("usage: ./fdf map.fdf");
	matrix = read_map(*++argv);
	init_param(&PRM);
	draw(matrix);
	mlx_hook(PRM.win, ClientMessage, StructureNotifyMask, handle_message, matrix);
	mlx_key_hook(PRM.win, deal_key, matrix);
	mlx_loop(PRM.mlx);
}