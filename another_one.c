/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   another_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adugain <adugain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 10:36:49 by schiffer          #+#    #+#             */
/*   Updated: 2023/05/15 18:47:40 by adugain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minilibx/mlx.h"
#include <X11/keysym.h>
#include <X11/X.h>

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
	int	bpp;
	int endian
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



typedef struct s_fdf
{
        t_map   map;
	t_mlx	mlx;
	t_mod	mod;
	t_disp	disp;
}       t_fdf;

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

int	err_pars(char *line, char **tab)
{
	free(line);
	if (tab)
		free_tab(tab);
	return (0);
}

char	*check_point(char *line)
{
	if (*line == '-' || *line == '+')
		line++;
	while(*line != ' ' && *line != ',' && *line)
	{
		if (*line < '0' || *line > '9')
			return (NULL);
		line++;
	}
	if (*line == ',')
	{
		if (*(line + 1) != '0' || *(line + 2) != 'x')
			return (NULL);
		line += 3;
		while (*line != ' ' && *line)
		{
			if ((*line < '0' || *line > '9') && (*line < 'a' || *line > 'f')
				&& (*line < 'A' || *line > 'F'))
				return (NULL);
			line++;
		}
	}
	return (line);
}

int	check_line(t_fdf *fdf, char *line)
{
	int	x;

	x = 0;
	while (*line)
	{
		while (*line == ' ')
			line++;
		if (!(line = check_point(line)))
		{	
			return (0);
		}
		while (*line == ' ')
			line++;
		x++;
	}
	if (fdf->map.size.x != 0 && x != fdf->map.size.x)
		return (0);
	fdf->map.size.x = x;
	return (1);
}

size_t	get_base_index(const char *base, char c)
{
	int	index;

	index = 0;
	while (base[index] && base[index] != c)
		index++;
	return (!base[index] ? -1 : index);
}

int	get_color(char *pixel)
{
	const char	*hbase1;
	const char	*hbase2;
	int	c;
	
	hbase1 = "0123456789abcedf";
	hbase2 = "0123456789ABCEDF";
	if ((pixel = ft_strchr(pixel, ',')) == NULL)
		c = 0xffffff;
	else
	{
		c = 0;
		pixel += 3;
		while ((*pixel >= '0' || *pixel <= '9') && (*pixel >= 'a' || *pixel >= 'f')
			&& (*pixel >= 'A' || *pixel <= 'F'))
		{
			c = c * 16 + (get_base_index(*pixel >= 'a' ? hbase1 : hbase2, *pixel));
			pixel++;
		}
	}
	return (c);
}

int	get_height(char *pixel, int *height)
{
	long int	h;
	char	sign;
	int		count;

	h = 0;
	count = 0;
	sign = *pixel == '+' || *pixel == '-' ? -(*pixel++ - 44) : 1;
	while (*pixel == '0' && *pixel)
		pixel++;
	while (*pixel >= '0' && *pixel <= '9')
	{
		h = h * 10 + (*pixel - '0');
		count++;
		pixel++;
	}
	h *= sign;
	if (h < INT_MIN || h > INT_MAX || count > 11)
		return (0);
	else
	{
		*height = h;
		return (1);
	}
	
}

t_point	*height_n_color(t_fdf *fdf, char **tab)
{
	int	i;
	t_point	*line;

	i = 0;
	if (!(line = malloc(sizeof(t_point) * fdf->map.size.x)))
		return (NULL);
	while (tab[i])
	{
		if (!(get_height(tab[i], &line[i].height)))
			return (NULL);
		line[i].color = get_color(tab[i]);
		i++;
	}
	return (line);
}

int	fill_tab(t_fdf *fdf, char **tab)
{
	int	i;
	t_point	**tmp;

	if (!(tmp = malloc(sizeof(t_point *) * fdf->map.size.y)))
		return (0);
	i = fdf->map.size.y - 1;
	if (!(tmp[i] = height_n_color(fdf, tab)))
		return (0);
	if (fdf->map.map)
	{
		while (--i >= 0)
			tmp[i] = fdf->map.map[i];
		free(fdf->map.map);
	}
	fdf->map.map = tmp;
	return (1);
}

int    parse_map(t_fdf *fdf, char *file)
{
        int	fd;
        char	**tab;
	char	*line;
	
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (false);
	while ((line = get_next_line(fd)) != NULL)
	{
		if (!check_line(fdf, line))
			return(err_pars(line, NULL));
		if (!(tab = ft_split(line, ' ')))
			return (err_pars(line, NULL));
		fdf->map.size.y++;
		if (!(fill_tab(fdf, tab)))
			return (err_pars(line, tab));
		free_tab(tab);
		tab = NULL;
		free(line);
	}
	free(line);
	close(fd);
	return (1);
}

			/*^^^^Parsing^^^^*/

void	init(t_fdf *fdf)
{
	fdf->mlx.win_size.x = 1200;
	fdf->mlx.win_size.y = 800;
	fdf->mod.height_mod = 4;
	fdf->mod.zoom = 10;
	fdf->mod.angle_mod = 30;
	fdf->mod.pos.x = fdf->mlx.win_size.x / 2;
	fdf->mod.mod.y = fdf->mlx.win_size.y / 2;
}

		/*^^^^Window and features init^^^^*/


int main (int ac, char **av)
{
        t_fdf   fdf;
        
        if (ac == 2)
        {
                ft_memset(&fdf, 0, sizeof(t_fdf));
                if(parse_map(&fdf, av[1]))
		{
			init(&fdf);
		}
		else
		{
			free(fdf.map);
			ft_printf("Error\n");
		}
        }
        else
                ft_printf("usage: %s map.fdf\n", av[0]);
        return (0);
}