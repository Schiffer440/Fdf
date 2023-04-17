/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adugain <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 11:42:21 by adugain           #+#    #+#             */
/*   Updated: 2022/11/14 11:42:23 by adugain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if ((little[0] == '\0'))
		return ((char *)big);
	while (i < len && big[i])
	{
		j = 0;
		while (little[j] == big[i + j] && i + j < len)
		{
			if (little[j + 1] == '\0')
				return ((char *)big + i);
		j++;
		}
	i++;
	}
	return (0);
}

/*#include <stdio.h>
int main ()
{
	char *empty = (char *)"";
	printf("%s\n", ft_strnstr("", "coucou", -1));
}*/