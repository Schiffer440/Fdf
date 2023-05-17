/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   squeex.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adugain <adugain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:15:40 by adugain           #+#    #+#             */
/*   Updated: 2023/05/17 16:41:48 by adugain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "libft/libft.h"

# include "libft/libft.h"
# include "minilibx/mlx.h"
# include <X11/keysym.h>
# include <X11/X.h>

# define WIN_X 1200
# define WIN_Y 800
# define RED_PIXEL 0xFF0000
# define GREEN_PIXEL 0x00FF00

typedef	struct	s_mlx
{
	void	*mlx;
	void	*win;
}	t_mlx;

typedef	struct	s_fdf
{
	t_mlx	mlx;
}	t_fdf;

#endif