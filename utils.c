/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adugain <adugain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 18:18:43 by adugain           #+#    #+#             */
/*   Updated: 2023/04/03 10:55:46 by adugain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

typedef	struct s_matrix
{
	int	fd;
	int	m_x;
	int	m_y;
	void	*mlx_ptr;
	void	*win_ptr;
	int	**tab;
	int	zoom;
	
}	t_matrix;

typedef struct data
{
	int	x;
	int	y;
	int	z;
	int	x1;
	int	y1;
	int	z1;
	float	x_step;
	float	y_step;
}	data;

void    free_matrix(int **tab, t_matrix *matrix)
{
    int    i;

    i = 0;
    while (i < matrix->m_y)
    {
        free(tab[i]);
        i++;
    }
    free(tab);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	print_matrix(t_matrix *matrix)
{
	int	i;
	int	j;
	
	i = 0;
	j = 0;
	while (i < matrix->m_y)
	{
		j = 0;
		while(j < matrix->m_x)
		{
			ft_printf("%d", matrix->tab[i][j]);
			j++;
		}
		ft_printf("\n");
		i++;
	}
}

void	fill_matrix(t_matrix *matrix, char *map)
{
	int	i;
	int	j;
	char	*line;
	char	**data;
	
	i = 0;
	matrix->fd = open(map, O_RDONLY);
	line = get_next_line(matrix->fd);
	data = ft_split(line, ' ');
	while (i < matrix->m_y)
	{
		j = 0;
		while (j < matrix->m_x)
		{
			matrix->tab[i][j] = ft_atoi((char *)data[j]);
			j++;
		}
		free(line);
		free_tab(data);
		line = get_next_line(matrix->fd);
		data = ft_split(line, ' ');
		i++;
	}
}

void	get_wrecked(char *str)
{
	if (str[strlen(str) - 1] == '\n' && str)
		str[strlen(str) - 1] = '\0';
	else
		return ;
}

int	get_matrix_base(t_matrix *matrix, char *map)
{
	char	*line;
	
	matrix->fd = open(map, O_RDONLY);
	line = get_next_line(matrix->fd);
	get_wrecked(line);
	matrix->m_x = wordcount(line, ' ');
	matrix->m_y += 1;
	free(line);
	while (line)
	{
		line = get_next_line(matrix->fd);
		ft_printf("line:%s", line);
		if (line != NULL)
			get_wrecked(line);
		if (line != NULL && matrix->m_x == wordcount(line, ' '))
		{
			ft_printf("line check:%d\nm_x:%d\n\n", wordcount(line, ' '), matrix->m_x);
			free(line);
			matrix->m_y++;
		}
		else if ((line != NULL && matrix->m_x != wordcount(line, ' ')))
		{
			close(matrix->fd);
			return(0);
		}
	}
	close(matrix->fd);
	return (1);
}

void	create_matrix(t_matrix *matrix)
{
	int	i;

	i = 0;
	matrix->tab = malloc(sizeof(int*) * matrix->m_y);
	while (i < matrix->m_y)
	{
		ft_printf("creating...\n");
		matrix->tab[i] = malloc(sizeof(int) * matrix->m_x);
		i++;
	}
}

int	gen_matrix(char *map, t_matrix *matrix)
{
	matrix->m_x = 0;
	matrix->m_y = 0;
	
	if (get_matrix_base(matrix, map) == 0)
			return (0);
	create_matrix(matrix);
	fill_matrix(matrix, map);
	print_matrix(matrix);
	//free_matrix(matrix->tab, matrix);
	return (1);
	//ft_printf("m_y:%d\nm_x:%d", matrix.m_y, matrix.m_x);
}

int	handle_no_event(void *matrix)
{
	return(0);
}

int	handle_keyrelease(int keysym, t_matrix *matrix)
{
	printf("Keypress: %d\n", keysym);
	return (0);
}

int	handle_keypress(int keysym, t_matrix *matrix)
{
	if (keysym == XK_Escape)
	{	
		mlx_destroy_window(matrix->mlx_ptr, matrix->win_ptr);
		mlx_destroy_display(matrix->mlx_ptr);
	}
	/*if (keysym == XK_l)
		draw_line(matrix);*/
	return (0);
}

int	max_op(float a, float b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

float	abs_f(float nb)
{
	if (nb < 0)
		nb *= -1;
	return (nb);
}

int	color(int x, int y, t_matrix *matrix)
{
	int	z;
	int	z1;

	z = matrix->tab[y][x];
	ft_printf("z:%d\n", z);
	if (z != 0)
		return (0xe80c0c);
	else
		return (0xffffff);
}

void	bresenham(float x, float y, float x1, float y1, t_matrix *matrix, int i)
{
	float	x_step;
	float	y_step;
	int	max;
	int	z;
	int	z1;
	
	z = color(x, y, matrix);
	x *= matrix->zoom;
	y *= 20;
	x1 *= matrix->zoom;
	y1 *= 20;
	x += i + 1;
	y += i + 1;
	x1 += i + 1;
	y1 += i + 1;
	
	x_step = x1 - x;
	y_step = y1 - y;
	max = max_op(abs_f(x_step), abs_f(y_step));
	x_step /= max;
	y_step /= max;
	while((int)(x-x1) || (int)(y-y1))
	{
		mlx_pixel_put(matrix->mlx_ptr, matrix->win_ptr, x, y, z);
		x += x_step;
		y += y_step;
	}
}

void	map_display(t_matrix *matrix)
{
	int	x;
	int	y;
	int	i;

	y = 0;
	i = 0;
	while(y < matrix->m_y)
	{
		x = 0;
		while (x <= matrix->m_x)
		{
			if (x < matrix->m_x)
			{
				bresenham(x, y, x + 1, y, matrix, i);
			}
				
			if (y < matrix->m_y - 1)
				bresenham(x, y, x, y + 1, matrix, i);
			x++;
			i++;
		}
		y++;
	}
}

int	main(int ac,char **av)
{
	t_matrix	matrix;
	
	if (ac == 2)
	{
		if (gen_matrix(av[1], &matrix) != 1)
			return (0);
	}
	else 
		return (0);
	matrix.zoom = 20;
	matrix.mlx_ptr = mlx_init();
	matrix.win_ptr = mlx_new_window(matrix.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "FdF");
	mlx_loop_hook(matrix.mlx_ptr, &handle_no_event, &matrix);
	mlx_hook(matrix.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &matrix);
	mlx_hook(matrix.win_ptr, KeyRelease, KeyReleaseMask, &handle_keyrelease, &matrix);
	map_display(&matrix);
	mlx_loop(matrix.mlx_ptr);
	//mlx_destroy_window(matrix.mlx_ptr, matrix.win_ptr);
	//mlx_destroy_display(matrix.mlx_ptr);
	free(matrix.mlx_ptr);
	free_matrix(matrix.tab, &matrix);
}