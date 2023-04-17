/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adugain <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 12:56:21 by adugain           #+#    #+#             */
/*   Updated: 2022/11/11 12:56:22 by adugain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;

	i = 0;
	str = (unsigned char *)s;
	while (n > i && str[i] != (unsigned char)c)
		i++;
	if (n == i)
		return (0);
	return ((void *)str + i);
}

/*#include <stdio.h>
int main ()
{
	char s[] = {0, 1, 2 ,3 ,4 ,5};
	printf("%s\n", s);
	ft_memchr(s, 2 + 256, 3);
	printf("%p\n", ft_memchr(s, 2 + 256, 3));
	printf("%s\n", s);
}*/