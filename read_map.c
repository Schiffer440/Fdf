/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adugain <adugain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 11:38:11 by adugain           #+#    #+#             */
/*   Updated: 2023/05/31 12:20:01 by adugain          ###   ########.fr       */
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

static t_fdf	**set_map(char *file_name)
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