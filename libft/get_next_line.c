/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adugain <adugain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 15:42:17 by adugain           #+#    #+#             */
/*   Updated: 2023/03/13 15:46:45 by adugain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

static char	*clean_stash(char *stash)
{
	int		i;
	int		j;
	int		len;
	char	*n_stash;

	i = 0;
	j = 0;
	while (stash[i] != '\n' && stash[i])
		i++;
	if (!stash[i])
		return (free(stash), NULL);
	len = ft_strlen_gnl(stash) - i;
	n_stash = malloc(sizeof(char) * (len + 1));
	if (!n_stash)
		return (free(stash), NULL);
	i++;
	while (stash[i])
		n_stash[j++] = stash[i++];
	n_stash[j] = '\0';
	free(stash);
	return (n_stash);
}

static char	*read_and_stash(int fd, char *stash)
{
	int		readed;
	char	*buf;

	readed = 1;
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	while (!ft_strchr_gnl(stash, '\n') && readed != 0)
	{
		readed = read(fd, buf, BUFFER_SIZE);
		if (readed == -1)
			return (free(buf), NULL);
		buf[readed] = '\0';
		stash = ft_strjoin_gnl(stash, buf);
	}
	free(buf);
	return (stash);
}

static char	*write_line(char *stash)
{
	int		i;
	char	*line;

	i = 0;
	if (!stash[i])
		return (NULL);
	while (stash[i] != '\n' && stash[i])
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (free(stash), NULL);
	i = 0;
	while (stash[i] != '\n' && stash[i])
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = read_and_stash(fd, stash);
	if (!stash)
		return (NULL);
	line = write_line(stash);
	stash = clean_stash(stash);
	return (line);
}
