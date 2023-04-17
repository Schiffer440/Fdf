/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adugain <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 11:18:22 by adugain           #+#    #+#             */
/*   Updated: 2023/03/31 14:09:26 by adugain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*free_split(char **tab, int pos)
{
	while (pos >= 0)
	{
		free(tab[pos]);
		pos--;
	}
	free (tab);
	return (NULL);
}

static int	wordcount(char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == c && s[i])
			i++;
		else
		{
			while (s[i] != c && s[i])
			{
				i++;
			}
		count++;
		}
	}
	return (count);
}

static char	*filltab(char *s, char c, char **tab, int count)
{
	int		i;
	int		len;
	char	*str;

	i = 0;
	len = 0;
	while (s[i] == c)
		s++;
	while (s[i] != c && s[i])
	{
		i++;
		len++;
	}
	str = malloc(sizeof(char) * len + 1);
	if (!str)
		return (free_split(tab, count));
	i = 0;
	while (i < len)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		count;

	if (!s)
		return (0);
	count = 0;
	tab = malloc(sizeof(char *) * (wordcount((char *)s, c) + 1));
	if (!tab)
		return (0);
	while (*s)
	{
		while (s[0] == c && *s)
			s++;
		if (*s)
		{
			tab[count] = filltab((char *)s, c, tab, count);
			if (tab[count] == 0)
				return (0);
			count++;
		}
		while (s[0] != c && *s)
			s++;
	}
	tab[count] = 0;
	return (tab);
}

// #include <stdio.h>
// int main() 
// {
//     int i;
//     char **tab = ft_split("  tripouille  42  ", ' ');

//     i = 0;
//     while(tab[i])
//     {
//         printf("%s\n", tab[i]);
//         i++;
//     }
//   return (0);
// }
