/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   another_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adugain <adugain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 10:36:49 by schiffer          #+#    #+#             */
/*   Updated: 2023/05/17 16:55:31 by adugain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	fdf->mod.angle_mod = 15;
	fdf->mod.pos.x = fdf->mlx.win_size.x / 2;
	fdf->mod.pos.y = fdf->mlx.win_size.y / 2;
}

		/*^^^^Window and features init^^^^*/

void	free_map(t_map *map)
{
	int	i;

	i = 0;

	while (i < map->size.y)
	{
		free(map->map[i]);
		i++;
	}
	free(map->map);
}

int	fdf_exit(t_fdf *fdf)
{
	free_map(&fdf->map);
	if (fdf->mlx.mlx && fdf->mlx.window)
		mlx_destroy_window(fdf->mlx.mlx, fdf->mlx.window);
	if (fdf->mlx.mlx && fdf->mlx.image)
		mlx_destroy_image(fdf->mlx.mlx, fdf->mlx.image);
	exit(fdf->mod.exit_val);
	return (0);
}

			/*^^^^Exit fdf^^^^*/

void	mod_move(t_fdf *fdf, int keycode)
{
	if (keycode == XK_KP_Add)
		fdf->mod.zoom += 3;
	if (keycode == XK_KP_Subtract)
		fdf->mod.zoom -= 3;
	if (keycode == XK_KP_9)
		fdf->mod.height_mod++;
	if (keycode == XK_KP_3)
		fdf->mod.height_mod--;
	
}

int	key_hook(int keycode, t_fdf *fdf)
{
	if (keycode == XK_Escape)
		fdf_exit(fdf);
	mod_move(fdf, keycode);
	draw_map(fdf);
	return (0);
}

int	img_move(int keycode, t_fdf *fdf)
{
	if (keycode == XK_Up || keycode == XK_W)
		fdf->mod.pos.y -= 20;
	if (keycode == XK_Down || keycode == XK_S)
		fdf->mod.pos.y += 20;
	if (keycode == XK_Left || keycode == XK_A)
		fdf->mod.pos.x -= 20;
	if (keycode == XK_Right || keycode == XK_D)
		fdf->mod.pos.x += 20;
	if (keycode == XK_Q || keycode == XK_KP_8)
		fdf->mod.angle_mod += 3;
	if (keycode == XK_E || keycode == XK_KP_2)
		fdf->mod.angle_mod -= 3;
	draw_map(fdf);
	return (0);
}

void	add_keyhook(t_fdf *fdf)
{
	mlx_key_hook(fdf->mlx.window, key_hook, fdf);
	mlx_hook(fdf->mlx.window, KeyPress, 0, img_move, fdf);
	mlx_hook(fdf->mlx.window, DestroyNotify, 0, fdf_exit, fdf);
	
}

			/*^^^^Keyhooks^^^^*/

double	deg_to_rad(int degree)
{
	return (degree * (float)3.14159265 / (float)180.0);
}

t_dim	ft_iso(t_fdf *fdf, int x, int y, int z)
{
	t_dim	n_dim;
	int	angle;
	double	zoom;

	if (fdf->mod.angle_mod > 45)
		angle = 45;
	else if (fdf->mod.angle_mod < -45)
		angle = -45;
	else
		angle = fdf->mod.angle_mod;
	zoom = fdf->mod.zoom < 0 ? 1 / (double)-(fdf->mod.zoom) : fdf->mod.zoom;
	x -= fdf->map.size.x / 2;
	y -= fdf->map.size.y / 2;
	x *= zoom;
	y *= zoom;
	z *= zoom * fdf->mod.height_mod / 10;
	n_dim.x = (x - y) * cos(deg_to_rad(angle));
	n_dim.y = (x + y) * sin(deg_to_rad(angle)) - z;
	n_dim.x += fdf->mod.pos.x;
	n_dim.y += fdf->mod.pos.y;
	return (n_dim);
}


			/*^^^^Iso^^^^*/

void	draw_line(int max_step, t_mlx *mlx, t_pixel *pix1, t_pixel *pix2)
{
	float	x_step;
	float	y_step;

	x_step = pix1->x - pix2->x;
	y_step = pix1->y - pix2->y;
	x_step /= max_step;
	y_step /= max_step;
	while((pix1->x - pix2->x) || (pix1->y - pix2->y))
	{
		ft_printf("check2\n");
		mlx_pixel_put(mlx->mlx, mlx->window, pix1->x, pix1->y, pix1->color);
		pix1->x += (int)x_step; 
		pix1->y += (int)y_step;
	}
}

void	swap_fdf(int *a, int *b)
{
	int	c;

	c = *a;
	*a = *b;
	*b = c;
}

void	put_line(t_mlx *mlx, t_pixel *pix1, t_pixel *pix2)
{
	int	max_step;

	max_step = ft_abs(pix2->y - pix1->y) > ft_abs(pix2->x - pix1->x);
	if (max_step)
	{
		swap_fdf(&pix1->x, &pix1->y);
		swap_fdf(&pix2->x, &pix2->y);
	}
	if (pix1->x > pix2->x)
	{
		swap_fdf(&pix1->x, &pix2->x);
		swap_fdf(&pix1->y, &pix2->y);
		swap_fdf(&pix1->color, &pix2->color);
	}
	draw_line(max_step, mlx, pix1, pix2);
}

void	bresenham(t_fdf *fdf, t_dim p1, t_dim p2)
{
	t_pixel	pix1;
	t_pixel	pix2;
	t_dim	tmp;

	tmp = ft_iso(fdf, p1.x, p1.y, fdf->map.map[p1.x][p1.y].height);
	pix1.x = tmp.x;
	pix1.y = tmp.y;
	pix1.color = fdf->map.map[p1.x][p1.y].color;
	tmp = ft_iso(fdf, p2.x, p2.y, fdf->map.map[p2.x][p2.y].height);
	pix2.x = tmp.x;
	pix2.y = tmp.y;
	pix2.color = fdf->map.map[p2.x][p2.y].color;
	if ((pix1.x > 0 && pix1.x < fdf->mlx.win_size.x
		&& pix1.y > 0 && pix1.y < fdf->mlx.win_size.y)
		||(pix2.x > 0 && pix2.x < fdf->mlx.win_size.x
		&& pix2.y > 0 && pix2.y < fdf->mlx.win_size.y))
		put_line(&fdf->mlx, &pix1, &pix2);
}

void	draw_map(t_fdf *fdf)
{
	int	i;
	int	j;

	i = 0;
	while(i < fdf->map.size.y)
	{
		j= 0;
		while (j < fdf->map.size.x)
		{
			if (i != 0)
				bresenham(fdf, (t_dim){i, j}, (t_dim){i - 1, j});
			if (j != 0)
				bresenham(fdf, (t_dim){i, j}, (t_dim){i, j - 1});
			j++;
		}
		i++;
	}
}

			/*^^^^Drawings^^^^*/

int	map_display(t_fdf *fdf)
{
	fdf->mlx.mlx = mlx_init();
	if (fdf->mlx.mlx != NULL)
	{
		fdf->mlx.window = mlx_new_window(fdf->mlx.mlx, fdf->mlx.win_size.x,
										fdf->mlx.win_size.y, "FdF");
		if (fdf->mlx.window != NULL)
		{
			fdf->mlx.image = mlx_new_image(fdf->mlx.mlx,
				fdf->mlx.win_size.x, fdf->mlx.win_size.y);
			if (fdf->mlx.image != NULL)
			{
				fdf->mlx.buf = mlx_get_data_addr(fdf->mlx.image,
					&fdf->mlx.bpp, &fdf->mlx.buf_wid, &fdf->mlx.endian);
				mlx_put_image_to_window(fdf->mlx.mlx, fdf->mlx.window,
					fdf->mlx.image, 0, 0);
				add_keyhook(fdf);
				draw_map(fdf);
				mlx_loop(fdf->mlx.mlx);
				return (0);
			}
			
		}
	}
	return (1);
}

int main (int ac, char **av)
{
        t_fdf   fdf;
        
        if (ac == 2)
        {
                ft_memset(&fdf, 0, sizeof(t_fdf));
                if(parse_map(&fdf, av[1]))
		{
			init(&fdf);
			if (map_display(&fdf) == 0)
				return (ft_printf("Display error...\n"));
		}
		else
		{
			free_map(&fdf.map);
			ft_printf("Parsing error...\n");
		}
        }
        else
                ft_printf("usage: %s map.fdf\n", av[0]);
        return (0);
}