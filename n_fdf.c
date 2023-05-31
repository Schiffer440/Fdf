/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_fdf.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adugain <adugain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 11:30:37 by adugain           #+#    #+#             */
/*   Updated: 2023/05/31 10:58:38 by adugain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
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

void	ft_error(char *msg)
{
	ft_printf("%s\n", msg);
	exit(1);
}

void	init_param(t_fdf *param)
{
	param->scale = 20;
	param->z_scale = 1;
	param->is_isometric = 1;
	param->angle = 0.523599;
	param->win_x = 1200;
	param->win_y = 800;
	param->shift_x = param->win_x / 3;
	param->shift_y = param->win_y / 3;
	param->mlx = mlx_init();
	param->win =\
	mlx_new_window(param->mlx, param->win_x, param->win_y, "FdF");
}

t_fdf	**set_map(char *file_name)
{
	t_fdf	**new;
	int		x;
	int		y;
	int		fd;
	char	*line;

	if ((fd = open(file_name, O_RDONLY, 0)) <= 0)
		ft_error("file does not exist");
	line = get_next_line(fd);
	x = ft_wordcount(line, ' ');
	free(line);
	y = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		y++;
		free(line);
	}
	free(line);
	new = (t_fdf **)malloc(sizeof(t_fdf *) * (++y + 1));
	while (y > 0)
		new[--y] = (t_fdf *)malloc(sizeof(t_fdf) * (x + 1));
	close(fd);
	return (new);
}

int		fill_map(char *line, t_fdf **map, int y)
{
	char	**point;
	int		x;

	point = ft_split(line, ' ');
	x = 0;
	while (point[x])
	{
		map[y][x].z = ft_atoi(point[x]);
		map[y][x].x = x;
		map[y][x].y = y;
		map[y][x].is_last = 0;
		free(point[x++]);
	}
	free(point);
	free(line);
	map[y][--x].is_last = 1;
	return (x);
}

float	fmodule(float i)
{
	return (i < 0) ? -i : i;
}

void	zoom(t_fdf *a, t_fdf *b, t_fdf *param)
{
	a->x *= param->scale;
	a->y *= param->scale;
	b->x *= param->scale;
	b->y *= param->scale;
	a->z *= param->z_scale;
	b->z *= param->z_scale;
}

void	isometric(t_fdf *fdf, double angle)
{
	fdf->x = (fdf->x - fdf->y) * cos(angle);
	fdf->y = (fdf->x + fdf->y) * sin(angle) - fdf->z;
}

void	set_param(t_fdf *a, t_fdf *b, t_fdf *param)
{
	zoom(a, b, param);
	if (param->is_isometric)
	{
		isometric(a, param->angle);
		isometric(b, param->angle);
	}
	a->x += param->shift_x;
	a->y += param->shift_y;
	b->x += param->shift_x;
	b->y += param->shift_y;
}

void	do_key(int key, t_fdf **matrix)
{
	if (key == XK_KP_Add)
		PRM.scale += 3;
	if (key == XK_KP_Subtract)
		PRM.scale -= 3;
	if (key == XK_z)
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
	if (key == XK_I)
		PRM.is_isometric = (PRM.is_isometric) ? 0 : 1;
	if (key == XK_q)
		PRM.angle += 0.05;
	if (key == XK_d)
		PRM.angle -= 0.05;
}

void	draw_line(t_fdf a, t_fdf b, t_fdf *param)
{
	float	step_x;
	float	step_y;
	float	max;
	int		color;

	set_param(&a, &b, param);
	step_x = b.x - a.x;
	step_y = b.y - a.y;
	max = MAX(fmodule(step_x), fmodule(step_y));
	step_x /= max;
	step_y /= max;
	color = (b.z || a.z) ? 0xfc0345 : 0xBBFAFF;
	color = (b.z != a.z) ? 0xfc031c : color;
	while ((int)(a.x - b.x) || (int)(a.y - b.y))
	{
		mlx_pixel_put(param->mlx, param->win, a.x, a.y, color);
		a.x += step_x;
		a.y += step_y;
		if (a.x > param->win_x || a.y > param->win_y || a.y < 0 || a.x < 0)
			break ;
	}
}

void	draw(t_fdf **matrix)
{
	int		y;
	int		x;

	y = 0;
	while (matrix[y])
	{
		x = 0;
		while (1)
		{
			if (matrix[y + 1])
				draw_line(matrix[y][x], matrix[y + 1][x], &PRM);
			if (!matrix[y][x].is_last)
				draw_line(matrix[y][x], matrix[y][x + 1], &PRM);
			if (matrix[y][x].is_last)
				break ;
			x++;
		}
		y++;
	}
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

t_fdf	**read_map(char *file)
{
	t_fdf	**map;
	int		y;
	int		fd;
	char	*line;

	map = set_map(file);
	fd = open(file, O_RDONLY, 0);
	y = 0;
	while ((line = get_next_line(fd)) != NULL)
		fill_map(line, map, y++);
	free(line);
	map[y] = NULL;
	close(fd);
	return (map);
}

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