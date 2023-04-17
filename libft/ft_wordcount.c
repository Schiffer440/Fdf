/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wordcount.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adugain <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 08:07:32 by adugain           #+#    #+#             */
/*   Updated: 2023/03/31 14:08:32 by adugain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_wordcount(char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] || s[i] == '\n')
	{
		if (s[i] == c && s[i])
			i++;
		else
		{
			while (s[i] != c && s[i])
			{
				i++;
			}
		count++;
		}
	}
	return (count);
}
