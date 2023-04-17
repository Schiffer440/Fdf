/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adugain <adugain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 10:33:26 by adugain           #+#    #+#             */
/*   Updated: 2022/12/08 17:11:10 by adugain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	long unsigned int	i;

	i = 0;
	if (!dest && !src)
		return (0);
	while (i < n)
	{
		*((char *)dest + i) = *((char *) src + i);
		i++;
	}
	return (dest);
}
