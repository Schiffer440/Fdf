/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adugain <adugain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 10:49:41 by adugain           #+#    #+#             */
/*   Updated: 2022/12/08 17:12:08 by adugain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ischarset(const char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
	i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		l;
	char	*trim;

	i = -1;
	if (!s1)
		return (0);
	while (s1 && ischarset(s1[0], set) != 0)
		s1++;
	l = ft_strlen(s1);
	while (s1 && ischarset(s1[l - 1], set) != 0 && l != 0)
		l--;
	if (l == 0)
		return (ft_strdup(""));
	trim = malloc(sizeof(char) * l + 1);
	if (!trim)
		return (0);
	while (++i < l)
		trim[i] = s1[i];
	trim[l] = '\0';
	return (trim);
}
