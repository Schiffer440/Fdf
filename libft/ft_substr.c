/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adugain <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:45:04 by adugain           #+#    #+#             */
/*   Updated: 2022/11/14 15:45:05 by adugain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*str;
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	if (!s || ft_strlen(s) < start)
		return (ft_strdup(""));
	if (ft_strlen(s) - start < len)
		str = malloc(sizeof(*s) * (ft_strlen(s) - start + 1));
	else
		str = malloc(sizeof(*s) * (len + 1));
	if (!str)
		return (0);
	while (s[i] != '\0')
	{
		if (i >= start && j < len)
		{
			str[j] = s[i];
			j++;
		}
	i++;
	}
	str[j] = '\0';
	return (str);
}

/*#include <stdio.h>
int main ()
{
	char * s;
	s = ft_substr("tripouille", 100, 1);
	printf("%s\n", s);
}*/