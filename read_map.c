/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adugain <adugain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 11:38:11 by adugain           #+#    #+#             */
/*   Updated: 2023/07/18 17:14:03 by adugain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	fill_map(char *line, t_fdf **map, int y)
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

static int	get_x(int fd)
{
	char	*line;
	int	x;

	line = get_next_line(fd);
	if (line == NULL)
		return (0);
	x = ft_wordcount(line, ' ');
	free(line);
	
	return (x);
}

int	check_name(char *file)
{
	int	i;

	i = 0;
	while (file[i] != '.')
		file++;
	if (ft_strncmp(file, ".fdf", 4) != 0)
		return (0);
	else
		return (1);
}

int	get_y(char *line, int fd)
{
	int	y;

	y = 0;
	while (line != NULL)
	{
		y++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	return (y);
}

static t_fdf	**set_map(char *file_name)
{
	t_fdf	**new;
	int		x;
	int		y;
	int		fd;
	char	*line;
	
	if (!check_name(file_name))
		ft_error("wrong file");
	fd = open(file_name, O_RDONLY, 0);
	if (fd <= 0)
		ft_error("file does not exist");
	x = get_x(fd);
	line = get_next_line(fd);
	y = get_y(line, fd);
	if (x == 0 || y == 0)
		ft_error("Wrong map");
	new = (t_fdf **)malloc(sizeof(t_fdf *) * (++y + 1));
	while (y > 0)
		new[--y] = (t_fdf *)malloc(sizeof(t_fdf) * (x + 1));
	close(fd);
	return (new);
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
	line = get_next_line(fd);
	while (line != NULL)
	{
		fill_map(line, map, y++);
		line = get_next_line(fd);
	}
	free(line);
	map[y] = NULL;
	close(fd);
	return (map);
}
