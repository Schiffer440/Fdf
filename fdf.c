/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adugain <adugain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 09:01:36 by adugain           #+#    #+#             */
/*   Updated: 2023/05/10 11:31:39 by adugain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

int	ft_char_once(char *str)
{
	int	i;
	int	j;

	i = 0;
	if (str[0] == '\0' || str[1] == '\0')
		return (0);
	while (str[i] != '\0')
	{
		j = i + 1;
		while (str[i] != str[j] && str[j] != '\0')
			j++;
		if (str[i] == str[j] || str[i] == '+' || str[i] == '-')
			return (0);
		i++;
	}
	return (1);
}

int	convertion(char *str, char *base, int pos)
{
	int	nb;
	int	j;

	nb = 0;
	j = 0;
	while (base[j] != '\0')
	{
		if (str[pos] == base[j])
		{
			nb = nb * ft_strlen(base) + j;
			pos++;
			j = -1;
		}
		j++;
	}
	return (nb);
}

int	ft_atoi_base(char *str, char *base)
{
	int	sign;
	int	i;

	sign = 1;
	i = 0;
	if (ft_char_once(base) == 0)
		return (0);
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	return (sign * convertion(str, base, i));
}

typedef struct s_pixel
{
	int	val;
	int	color;
}	t_pixel;

typedef	struct s_matrix
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_pixel	**pixel;
	char	*str;
	int	m_x;
	int	m_y;
	int	**tab;

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


void    free_matrix(t_matrix *matrix)
{
    int    i;

    i = 0;
    while (i < matrix->m_y)
    {
        free(matrix->pixel[i]);
        i++;
    }
    free(matrix->pixel);
}

int	handle_keypress(int keysym, t_matrix *matrix)
{
	if (keysym == XK_Escape)
		mlx_destroy_window(matrix->mlx_ptr, matrix->win_ptr);
	return (0);
}

bool	parse_color(char *map, int *i)
{
	int	count;
	if(!(map[*i] == '0' && map[*i + 1] && map[*i + 1] == 'x'))
		return (false);
	*i += 2;
	count = 0;
	while (map[*i] && map[*i] != ' ')
	{
		if((map[*i] >= '0'  &&  map[*i] <= '9')
		|| (map[*i] >= 'a' && map[*i] <= 'f')
		|| (map[*i] >= 'A' && map[*i] <= 'F'))
		{
			++*i;
			count++;
		}	
		else
			return (false);
	}
	++*i;
	if (count > 8)
		return (false);
	else
		return (true);
		
}

bool	parse_digit(char *map, int *i)
{
	while (map[*i] && ft_isdigit(map[*i]))
		++*i;
	if (!*i || (map[*i - 1] == ' ' || map[*i - 1] == '-'))
		++*i;
	else if (map[*i] == ',')
	{
		++*i ;
		if (parse_color(map, i) == false)
			return (false);
		else
			return (true);
	}
	else if (!(map[*i] == ' ' || map[*i] == '\n'))
		return (false);
	return (true);
}

int	parse_map(char *map)
{
	int	i;
	
	i = 0;
	while (map[i])
	{
		if (ft_isdigit(map[i]))
		{	if (parse_digit(map, &i) == false)
				return (0);
		}
		else if (map[i] == '-' && map[i + 1] && ft_isdigit(map[i + 1]))
			i++;
		else if (map[i] == ' ')
			i++;
		else if (map[i] == '\n')
			i++;
		else
			return (0);
	}
	return (1);
}

void	malloc_tab(t_matrix *matrix)
{
	int	i;

	i = 0;
	matrix->pixel = malloc(matrix->m_y * sizeof(struct s_pixel*));
	while (i < matrix->m_y)
	{
		matrix->pixel[i]= malloc(matrix->m_x * sizeof(struct s_pixel));
		i++;
	}
}

void	get_dim(t_matrix *matrix, char *map)
{
	int	fd;
	int	word;
	char	*line;
	bool	first_line;

	fd = open(map, O_RDONLY);
	first_line = true;
	while ((line = get_next_line(fd)) != NULL)
	{
		ft_printf("dim=%d\n", matrix->m_y);
		if (first_line == true)
		{
			matrix->m_x = ft_wordcount(line, ' ');
		}
		else if (matrix->m_x != ft_wordcount(line, ' '))
			return ;
		first_line = false;
		matrix->m_y++;
		free(line);
	}
	close(fd);
}

void	pixel_n_colors(t_matrix *matrix, char *str, int *x, int *y)
{
	char **PnC;
	int i;
	
	i = 0;
	PnC = ft_split(str, ',');
	if (PnC[i] && PnC[i + 1])
	{
		matrix->pixel[*y][*x].val = ft_atoi(str);
		matrix->pixel[*y][*x].color = ft_atoi_base(PnC[i + 1] + 2, "0123456789ABCDEF");
	}
	else
	{
		matrix->pixel[*y][*x].val = ft_atoi(str);
		matrix->pixel[*y][*x].color = 0xffffff;
	}
}


void	fill_tab(t_matrix *matrix, char *line)
{
	int	x;
	int	z;
	char	**dot;

	z = 0;
	dot = ft_split(line, ' ');
	x = 0;
	while(x < matrix->m_x && dot[z])
	{
		pixel_n_colors(matrix, dot[z], &x, &matrix->m_y);
			z++;
			x++;
	}
	z = 0;
	while(dot[z])
	{
		free(dot[z]);
		z++;
	}
	free(dot);
}

void	read_map(t_matrix *matrix, char *map)
{
	int	fd;
	char	*line;
	
	get_dim(matrix, map);
	malloc_tab(matrix);
	fd = open(map, O_RDONLY);
	matrix->m_y = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		ft_printf("filling\n");
		if (parse_map(line) != 1)
			return ;
		fill_tab(matrix, line);
		matrix->m_y++;
		free(line);
	}
	close(fd);
}

bool	init(t_matrix *matrix)
{
	matrix->mlx_ptr = mlx_init();
	if (matrix->mlx_ptr == NULL)
		return(false);
	matrix->win_ptr = mlx_new_window(matrix->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "FdF");
	if (matrix->win_ptr == NULL)
		return (false);
	matrix->str = NULL;
	matrix->m_x = 0; 
	matrix->m_y = 0;
	return (true);
}

// void	fdf(t_matrix *matrix)
// {
// 	int	x;
// 	int	y;
	
// 	y = 0;
// 	malloc_tab(matrix);
// 	fill_tab(matrix);
// }

// void	print_matrix(t_matrix *matrix)
// {
// 	int	i;
// 	int	j;
	
// 	i = 0;
// 	j = 0;
// 	while (i < matrix->m_y)
// 	{
// 		j = 0;
// 		while(j < matrix->m_x)
// 		{
// 			ft_printf("val:%d\n", matrix->pixel[i][j].val);
// 			ft_printf("color:%s\n", matrix->pixel[i][j].color);
// 			j++;
// 		}
// 		ft_printf("\n");
// 		i++;
// 	}
// }

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

// int	color(int x, int y, t_matrix *matrix, int ch)
// {
// 	int	z;
// 	int	z1;
// 	z = matrix->tab[y][x];
// 	printf("hello\n");
// 	if (z != 0)
// 		return (2 * ch % 255 << 16 | 3 * ch % 255 << 8 | 4 * ch % 255);
		
// 	else
// 		return (0x88f5ef);
		
// }

void	ft_iso(float *x, float *y, int z)
{
	*x = (*x - *y) * cos(0.8);
	*y = (*x + *y) * sin(0.8) - z;
}

void	bresenham(data data, t_matrix *matrix)
{
	float	x_step;
	float	y_step;
	int	max;

	data.color = matrix->pixel[(int)data.y][(int)data.x].color;
	data.z = matrix->pixel[(int)data.y][(int)data.x].val;
	data.z1 = matrix->pixel[(int)data.y1][(int)data.x1].val;
	data.x *= 10;
	data.y *= 10;
	data.x1 *= 10;
	data.y1 *= 10;

	ft_iso(&data.x, &data.y, data.z);
	ft_iso(&data.x1, &data.y1, data.z1);
	data.x += WINDOW_WIDTH / 2;
	data.y +=  WINDOW_HEIGHT / 2;
	data.x1 +=  WINDOW_WIDTH / 2;
	data.y1 +=  WINDOW_HEIGHT / 2;

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

void	print_matrix(t_matrix *matrix)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	ft_printf("y=%d\nx=%d\n", matrix->m_y, matrix->m_x);
	while(y < matrix->m_y)
	{
		x = 0;
		while(x < matrix->m_x)
		{
			ft_printf("%d", matrix->pixel[y][x].val);
			x++;
		}
		ft_printf("\n");
		y++;
	}
}

int	main(int ac, char **av)
{
	t_matrix	matrix;
	
	if (ac != 2)
		return (0);
	if (init(&matrix) == false)
		return (0);
	read_map(&matrix, av[1]);
	ft_printf("y=%d\nx=%d\n", matrix.m_y, matrix.m_x);
	//fdf(&matrix);
	map_display(&matrix);
	//print_matrix(&matrix);
	mlx_loop_hook(matrix.mlx_ptr, &handle_keypress, &matrix);
	mlx_hook(matrix.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &matrix);
	mlx_loop(matrix.mlx_ptr);
	mlx_destroy_display(matrix.mlx_ptr);
	free(matrix.mlx_ptr);
	free_matrix(&matrix);
	return (0);
}
