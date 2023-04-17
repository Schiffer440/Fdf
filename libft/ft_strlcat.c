/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adugain <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:24:20 by adugain           #+#    #+#             */
/*   Updated: 2022/11/09 16:24:27 by adugain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t			i;
	size_t			len1;
	size_t			len2;

	if (size == 0)
		return (ft_strlen(src));
	i = 0;
	len1 = ft_strlen(dst);
	len2 = ft_strlen((char *)src);
	if (size <= len1)
		return (size + len2);
	while (len1 + i < size - 1 && src[i])
	{
		dst[len1 + i] = src[i];
		i++;
	}
	dst[len1 + i] = '\0';
	return (len1 + len2);
}

/*#include <stdio.h>
int main()
{
	char dest[30]; memset(dest, 0, 30);
	char * src = (char *)"AAAAAAAAA";
	ft_strlcat(dest, src, 17);
	printf("%ld\n", ft_strlcat(dest, src, 17));
	printf("%s\n", dest);
}*/