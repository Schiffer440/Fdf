/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adugain <adugain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 11:41:37 by adugain           #+#    #+#             */
/*   Updated: 2023/07/22 12:04:36 by adugain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// float	f_abs(float f)
// {
// 	if (f < 0)
// 		return (f * -1);
// 	else
// 		return (f);
// }

void	isometric(t_fdf *fdf, double angle)
{
	fdf->x = (fdf->x - fdf->y) * cos(angle);
	fdf->y = (fdf->x + fdf->y) * sin(angle / 2) - fdf->z;
}

void	free_matrix(t_fdf **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

int	change_iso(int iso)
{
	if (iso == 1)
		return (0);
	else
		return (1);
}
