/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adugain <adugain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 14:40:32 by adugain           #+#    #+#             */
/*   Updated: 2022/12/08 17:11:04 by adugain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	int				j;
	unsigned char	*a;
	unsigned char	*b;

	a = (unsigned char *)s1;
	b = (unsigned char *)s2;
	j = 0;
	i = 0;
	while (i < n)
	{
		if (a[j] != b[j])
			return (a[j] - b[j]);
		else
		{
			i++;
			j++;
		}
	}
	return (0);
}
