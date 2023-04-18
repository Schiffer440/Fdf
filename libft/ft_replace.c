/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adugain <adugain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 11:24:09 by adugain           #+#    #+#             */
/*   Updated: 2023/04/18 11:28:51 by adugain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*replace a by b*/
void	ft_replace(char *str, char a, char b)
{
	int	i;
	while (str[i])
	{
		if (str[i] == a)
			str[i] = b;
		i++;
	}
}