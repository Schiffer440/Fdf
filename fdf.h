/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adugain <adugain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 09:46:16 by adugain           #+#    #+#             */
/*   Updated: 2023/06/13 11:03:34 by adugain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "libft/libft.h"

# include "libft/libft.h"
#include "minilibx/mlx.h"
#include <X11/keysym.h>
#include <X11/X.h>
#define PRM matrix[0][0]

typedef struct	s_fdf
{
	float		x;
	float		y;
	float		z;
	int			is_last;

	int			color;
	int			scale;
	int			z_scale;
	int			shift_x;
	int			shift_y;
	int			is_isometric;
	double		angle;
	int			win_x;
	int			win_y;
	void		*mlx;
	void		*win;
}				t_fdf;

t_fdf	**read_map(char *file);
void	ft_error(char *msg);
void	init_param(t_fdf *param);
void	draw(t_fdf **matrix);
void	set_param(t_fdf *a, t_fdf *b, t_fdf *param);
float	f_abs(float i);
void	isometric(t_fdf *fdf, double angle);
void	zoom(t_fdf *a, t_fdf *b, t_fdf *param);
int		deal_key(int key, t_fdf **matrix);
int	handle_message(t_fdf **matrix);
void	free_matrix(t_fdf **matrix);

#endif