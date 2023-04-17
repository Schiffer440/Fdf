/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adugain <adugain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 17:40:50 by adugain           #+#    #+#             */
/*   Updated: 2023/03/13 15:53:11 by adugain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen_gnl(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	i = -1;
	j = 0;
	if (!s1)
	{
		s1 = malloc(sizeof(char *) * 1);
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (0);
	str = malloc(sizeof(char) * (ft_strlen_gnl(s1) + ft_strlen_gnl(s2)) + 1);
	if (!str)
		return (0);
	while (s1[++i])
		str[i] = s1[i];
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	free(s1);
	return (str);
}

char	*ft_strchr_gnl(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			return ((char *)s + i);
		else
			i++;
	}
	return (NULL);
}
