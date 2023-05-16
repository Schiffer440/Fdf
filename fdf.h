/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adugain <adugain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 09:46:16 by adugain           #+#    #+#             */
/*   Updated: 2023/05/16 17:34:49 by adugain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "libft/libft.h"

# include "libft/libft.h"
# include "minilibx/mlx.h"
# include <X11/keysym.h>
# include <X11/X.h>

typedef struct s_dim
{
        int     x;
        int     y;
}       t_dim;

typedef struct s_point
{
        int     color;
        int     height;
}       t_point;

typedef struct s_map
{
        t_point **map;
        t_dim  size;
}       t_map;

typedef	struct s_mlx
{
	void	*image;
	char	*buf;
	int		buf_wid;
	void	*window;
	void	*mlx;
	t_dim	win_size;
	int		bpp;
	int 		endian;
}	t_mlx;

typedef	struct s_mod
{
	bool	mod_helper;
	int		height_mod;
	t_dim	pos;
	int		zoom;
	int		angle_mod;
	int		exit_val;
	int		proj;
}	t_mod;

typedef	struct s_disp
{
	int				colortheme;
	int				bg_color;
	int				text_color;
	int				usage_color;
	unsigned int	(*get_col)(int	h);
}				t_disp;

typedef	struct s_pixel
{
	int	x;
	int	y;
	int	color;
}	t_pixel;


typedef struct s_fdf
{
        t_map   map;
	t_mlx	mlx;
	t_mod	mod;
	t_disp	disp;
}       t_fdf;

void	free_tab(char **tab);
int	err_pars(char *line, char **tab);
char	*check_point(char *line);
int	check_line(t_fdf *fdf, char *line);
size_t	get_base_index(const char *base, char c);
int	get_color(char *pixel);
int	get_height(char *pixel, int *height);
t_point	*height_n_color(t_fdf *fdf, char **tab);
int	fill_tab(t_fdf *fdf, char **tab);
int    parse_map(t_fdf *fdf, char *file);
void	init(t_fdf *fdf);
void	free_map(t_map *map);
int	fdf_exit(t_fdf *fdf);
void	mod_move(t_fdf *fdf, int keycode);
int	key_hook(int keycode, t_fdf *fdf);
int	img_move(int keycode, t_fdf *fdf);
void	add_keyhook(t_fdf *fdf);
double	deg_to_rad(int degree);
t_dim	ft_iso(t_fdf *fdf, int x, int y, int z);
void	draw_line(int max_step, t_mlx *mlx, t_pixel *pix1, t_pixel *pix2);
void	swap_fdf(int *a, int *b);
void	put_line(t_mlx *mlx, t_pixel *pix1, t_pixel *pix2);
void	bresenham(t_fdf *fdf, t_dim p1, t_dim p2);
void	draw_map(t_fdf *fdf);
int	map_display(t_fdf *fdf);

#endif