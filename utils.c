/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adugain <adugain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 11:41:37 by adugain           #+#    #+#             */
/*   Updated: 2023/07/21 16:54:56 by adugain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_error(char *msg)
{
	ft_printf("%s\n", msg);
	exit(1);
}

float	f_abs(float i)
{
	return (i < 0) ? -i : i;
}

void	isometric(t_fdf *fdf, double angle)
{
	fdf->x = (fdf->x - fdf->y) * cos(angle);
	fdf->y = (fdf->x + fdf->y) * sin(angle / 2) - fdf->z;
}

void	free_matrix(t_fdf **matrix)
{
	int	i;

	i = 0;
	while(matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);	
}