/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adugain <adugain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 11:47:20 by adugain           #+#    #+#             */
/*   Updated: 2022/12/08 17:11:44 by adugain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	int	i;
	int	len;

	if (!s)
		return ;
	len = ft_strlen(s);
	i = 0;
	while (i < len)
	{
		(*f)(i, s);
		i++;
		s++;
	}
}
