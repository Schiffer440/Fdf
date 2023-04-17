/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adugain <adugain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 12:06:17 by adugain           #+#    #+#             */
/*   Updated: 2022/12/08 17:11:14 by adugain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	char			*d;
	const char		*s;

	if (dest == 0 && src == 0)
		return (0);
	d = dest;
	s = src;
	i = -1;
	if (d > s)
	{
		while (n != 0)
		{
			d[n - 1] = s[n - 1];
			n--;
		}
	}
	else
		while (++i < n)
			d[i] = s[i];
	return (dest);
}
