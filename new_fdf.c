/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_fdf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adugain <adugain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 15:42:33 by adugain           #+#    #+#             */
/*   Updated: 2023/05/25 11:27:36 by adugain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minilibx/mlx.h"

typedef	struct s_dim
{
	int	x;
	int	y;
}	t_dim;


typedef struct s_mlx
{
	void    *mlx;
	void    *win;
}       t_mlx;

typedef struct s_map
{
	int     h;
	int     c;
}	t_map;

typedef struct s_img
{
        void    *mlx_img;
        char    *addr;
        int     bpp;
        int     line_len;
        int     endian;
}       t_img;

typedef struct s_fdf
{
	t_map   **map;
	t_mlx   mlx;
	t_img	img;
	t_dim	dim;
}       t_fdf;

			/*Struct init*/

int	is_hex(char c)
{
	if (ft_isdigit(c) == 1 || (c >= 'a' && c <= 'f') 
		|| (c >= 'A' && c <= 'F'))
		return (1);
	else
		return (0);
	
}
			
			/*Utils*/
int	parse_line(char *line)
{
	int	x;
	
	x = 0;
	while (*line)
	{
		while (*line == ' ')
			*line++;
		if (ft_isdigit(*line) == 1)
			*line++;
		else if (*line == ',')
		{
			while (*line != ' ')
				*line++;
		}
		if ((*line + 1) == ' ' || (*line + 1) == '\0')
			x++;
	}
	return (x);
}

void	add_line(char *line)
{
	char	**n_line;
	int	i;
	
}

void	parse_map(t_fdf *fdf, char *file)
{
	char	*line;
	int	fd;
	
	fdf->dim.y = 0;
	fd = open(file, O_RDONLY);
	while ((line = get_next_line(fd)) != NULL)
	{
		if (!parse_line(line))
			return ;
		else
			add_line(fdf, line);
		fdf->dim.y++;
		free (line);
	}
	close(fd);
}

			/*Parsing*/

int     main(int ac, char **av)
{
	t_fdf	fdf;

	if (ac == 2)
	{
		fdf.map = parse_map(&fdf, av[1]);
	}
	return (0);
}
