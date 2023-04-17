/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_merge.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adugain <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 18:18:43 by adugain           #+#    #+#             */
/*   Updated: 2023/04/12 11:10:07 by adugain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

typedef struct s_pixel
{
	int	nb;
	int	color;
}	t_pixel;

typedef struct s_dot
{
	t_pixel **pixels;
}	t_dot;
typedef	struct s_matrix
{
	int	fd;
	int	m_x;
	int	m_y;
	char	*str;
	void	*mlx_ptr;
	void	*win_ptr;
	t_dot	**tab;
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

bool	parse_colors(char *s, int *i)
{
	int	n;

	n = 0;
	while (s[*i + n] && (ft_isdigit(s[*i + n])) || s[*i + n] >= 'A' &&
		s[*i + n] <= 'F' || s[*i + n] >= 'a' && s[*i + n] <= 'f')
		n++;
	if (n > 8)
		return (false);
	*i += n;
	return (true);
}

bool	parse_digit(char *map, int *i)
{
	if (!*i || (map[*i - 1] == ' ' || map[*i - 1] == '-'))
		++*i;
	else
		return (false);
	while (map[*i] && ft_isdigit(map[*i]))
		++*i;
	if (map[*i] == ',')
	{
		if (map[*i + 1] == '0' && map[*i + 2] == 'x')
		{
			*i += 3;
			if(parse_colors(map, i) == false)
				return (false);
		}	
	}
	return (true);
}

int	parse_map(char *map)
{
	int	i;
	int	x_nb;
	
	i = 0;
	x_nb = 0;
	while (map[i] && map[i] != '\n')
	{
		if (ft_isdigit(map[i]))
		{
			if (parse_digit(map, &i) == false)
				return (0);
			x_nb++;
		}
		else if (map[i] == '-' && map[i + 1] && ft_isdigit(map[i + 1]))
			i++;
		else if (map[i] == ' ')
			i++;
		else
			return (0);
	}
	return (x_nb);
}

void	read_map(t_matrix *matrix, char *map)
{
	int	fd;
	int	word;
	char	*line;
	bool	first_line;
	
	word = 0;
	fd = open(map, O_RDONLY);
	first_line = true;
	while ((line = get_next_line(fd)) != NULL)
	{
		ft_printf("line");
		if (first_line == true)
		{
			matrix->str = ft_strdup(line);
			matrix->m_x = parse_map(line);
		}
		else if (matrix->m_x != parse_map(line))
			return ;
		if (first_line == false)
			matrix->str = ft_strjoin_gnl(matrix->str, line);
		matrix->m_y++;
		first_line = false;
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
	matrix->tab = 0;
	matrix->str = NULL;
	matrix->m_x = 0; 
	matrix->m_y = 0;
	return (true);
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

int	color(int x, int y, t_matrix *matrix)
{
	int	z;
	int	z1;

	z = matrix->tab[y]->pixels[x]->nb;
	if (z != 0)
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
	
	data.color = color(data.x, data.y, matrix);
	data.z = matrix->tab[(int)data.y]->pixels[(int)data.x]->nb;
	ft_printf("x:%d y:%d z:%d\n", data.x, data.y, data.z );
	data.z1 = matrix->tab[(int)data.y1]->pixels[(int)data.x1]->nb;
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
	while(data.y < matrix->m_y - 1)
	{
		data.x = 0;
		while (data.x < matrix->m_x - 1)
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

void	get_matrix(t_matrix *matrix)
{
	char	**pixel;
	int	i;
	int	j;
	int	k;
	
	pixel = ft_split(matrix->str, ' ');
	i = 0;
	k = 0;
	while (i < matrix->m_y - 1)
	{
		j = 0;
		while (j < matrix->m_x - 1)
		{
			ft_printf("%s ", pixel[k]);
			matrix->tab[i]->pixels[j]->nb = ft_atoi(pixel[k]);
			k++;
			j++;
		}
		i++;
	}
}

int	main(int ac,char **av)
{
	t_matrix	matrix;
	
	if (ac == 2)
	{
		if (!init(&matrix))
			return (0);
	}
	else 
		return (0);
	matrix.zoom = 20;
	ft_printf("reading..");
	read_map(&matrix, av[1]);
	ft_printf("creating...");
	create_matrix(&matrix);
	get_matrix(&matrix);
	ft_printf("-----\n");
	mlx_loop_hook(matrix.mlx_ptr, &handle_keypress, &matrix);
	mlx_hook(matrix.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &matrix);
	map_display(&matrix);
	mlx_loop(matrix.mlx_ptr);
	mlx_destroy_display(matrix.mlx_ptr);
	free(matrix.mlx_ptr);
	//free_matrix(matrix.tab, &matrix);
}