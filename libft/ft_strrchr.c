/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adugain <adugain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 11:29:47 by adugain           #+#    #+#             */
/*   Updated: 2022/12/08 17:12:03 by adugain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	l;

	l = ft_strlen(s);
	if (!s)
		return (0);
	while (l >= 0)
	{
		if (s[l] == (unsigned char)c)
			return ((char *)s + l);
		else
			l--;
	}
	return (0);
}
