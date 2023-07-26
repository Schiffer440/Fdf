/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adugain <adugain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 09:46:16 by adugain           #+#    #+#             */
/*   Updated: 2023/07/26 18:16:37 by adugain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "libft/libft.h"

# include "libft/libft.h"
# include "minilibx/mlx.h"
# include <X11/keysym.h>
# include <X11/X.h>
# define WIDTH 1000
# define HEIGHT 500

typedef struct s_fdf
{
	float		x;
	float		y;
	float		z;
	int			is_last;
	int			bpp;
	int			size_line;
	int			endian;
	void		*addr;
	int			map_x;
	int			map_y;
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
	void		*img;
}				t_fdf;

t_fdf	**read_map(char *file);
void	init_param(t_fdf *param);
void	draw(t_fdf **matrix);
void	set_param(t_fdf *a, t_fdf *b, t_fdf *param);
void	isometric(t_fdf *fdf, double angle);
void	zoom(t_fdf *a, t_fdf *b, t_fdf *param);
int		deal_key(int key, t_fdf **matrix);
int		handle_message(t_fdf **matrix);
void	free_matrix(t_fdf **matrix);
int		check_name(char *file);
int		ft_check_atoi(const char *str);
int		check_line(char *str);
int		change_iso(int iso);
void	draw2(t_fdf **matrix);
void	init_mlx(t_fdf	*mlx);

#endif