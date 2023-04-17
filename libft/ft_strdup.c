/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adugain <adugain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:39:57 by adugain           #+#    #+#             */
/*   Updated: 2022/12/08 17:11:41 by adugain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *src)
{
	char	*a;

	a = malloc(sizeof(char) * ft_strlen(src) + 1);
	if (a == 0)
		return (0);
	else
		ft_strlcpy(a, src, ft_strlen(src) + 1);
	return (a);
}
