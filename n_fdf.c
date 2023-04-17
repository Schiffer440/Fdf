/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_fdf.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adugain <adugain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 18:18:43 by adugain           #+#    #+#             */
/*   Updated: 2023/04/03 12:18:52 by adugain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

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
	float	x;
	float	y;
	int	z;
	float	x1;
	float	y1;
	int	z1;
	int	color;
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
	while (i < matrix->m_y - 1)
	{
		j = 0;
		while(j < matrix->m_x - 1)
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
	matrix->m_x = ft_wordcount(line, ' ');
	matrix->m_y += 1;
	free(line);
	while (line)
	{
		line = get_next_line(matrix->fd);
		ft_printf("line:%s", line);
		if (line != NULL)
			get_wrecked(line);
		if (line != NULL && matrix->m_x == ft_wordcount(line, ' '))
		{
			ft_printf("line check:%d\nm_x:%d\n\n", ft_wordcount(line, ' '), matrix->m_x);
			free(line);
			matrix->m_y++;
		}
		else if ((line != NULL && matrix->m_x != ft_wordcount(line, ' ')))
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
	matrix->tab = malloc(sizeof(int *) * matrix->m_y);
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
	return (1);
}

int	handle_keypress(int keysym, t_matrix *matrix)
{
	if (keysym == XK_Escape)
	{	
		mlx_destroy_window(matrix->mlx_ptr, matrix->win_ptr);
	}
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

int	color(data *data)
{
	if (data->z != 0 || data->z1 != 0)
		return (0xe80c0c);
	else
		return (0xffffff);
}

void	ft_iso(float *x, float *y, int z)
{
	ft_printf("------------------------------------");
	*x = (*x - *y) * cos(1);
	*y = (*x + *y) * sin(1) - z;
}

void	bresenham(data data, t_matrix *matrix)
{
	float	x_step;
	float	y_step;
	int	max;
	
	data.z = matrix->tab[(int)data.y][(int)data.x];
	data.z1 = matrix->tab[(int)data.y1][(int)data.x1];
	data.color = color(&data);
	ft_printf("x:%d y:%d z:%d\n", data.x, data.y, data.z );
	data.z1 = matrix->tab[(int)data.y1][(int)data.x1];
	data.x *= matrix->zoom;
	data.y *= matrix->zoom;
	data.x1 *= matrix->zoom;
	data.y1 *= matrix->zoom;

	ft_iso(&data.x, &data.y, data.z);
	ft_iso(&data.x1, &data.y1, data.z1);
	data.x += 250;
	data.y += 250;
	data.x1 += 250;
	data.y1 += 250;

	
	ft_printf("x:%d y:%d z:%d\n", data.x, data.y, data.z );
	x_step = data.x1 - data.x;
	y_step = data.y1 - data.y;
	max = max_op(abs_f(x_step), abs_f(y_step));
	x_step /= max;
	y_step /= max;
	while((int)(data.x - data.x1) || (int)(data.y - data.y1))
	{
		mlx_pixel_put(matrix->mlx_ptr, matrix->win_ptr, data.x, data.y, data.color);
		data.x += x_step; 
		data.y += y_step;
	}
}

void	map_display(t_matrix *matrix)
{
	data data;

	data.y = 0;
	while(data.y < matrix->m_y)
	{
		data.x = 0;
		while (data.x < matrix->m_x)
		{
			//ft_printf("x->%d\n", data.x);
			if (data.x < matrix->m_x - 1)
			{
				data.x1 = data.x + 1;
				data.y1 = data.y;
				bresenham(data, matrix);
			}
				
			if (data.y < matrix->m_y - 1)
			{
				data.x1 = data.x;
				data.y1 = data.y + 1;
				bresenham(data, matrix);
			}
			data.x++;
		}
		data.y++;
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
	mlx_loop_hook(matrix.mlx_ptr, &handle_keypress, &matrix);
	mlx_hook(matrix.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &matrix);
	map_display(&matrix);
	mlx_loop(matrix.mlx_ptr);
	mlx_destroy_display(matrix.mlx_ptr);
	free(matrix.mlx_ptr);
	free_matrix(matrix.tab, &matrix);
}