/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adugain <adugain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:01:22 by adugain           #+#    #+#             */
/*   Updated: 2022/12/08 17:11:58 by adugain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*u1;
	unsigned char	*u2;

	u1 = (unsigned char *)s1;
	u2 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (i < n && (u1[i] != '\0' || u2[i] != '\0'))
	{
		if (u1[i] != u2[i] && (u1[i] != '\0' || u2[i] != '\0'))
			return (u1[i] - u2[i]);
		else
			i++;
	}
	return (0);
}
