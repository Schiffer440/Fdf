/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adugain <adugain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 11:41:23 by adugain           #+#    #+#             */
/*   Updated: 2023/07/26 13:18:13 by adugain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	check_name(char *file)
{
	int	i;

	i = 0;
	while (file[i] != '.')
		file++;
	if (ft_strncmp(file, ".fdf", 4) != 0)
		return (0);
	else
		return (1);
}

int	ft_check_atoi(const char *str)
{
	int	i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' && str[i + 1] >= '0' && str[i + 1] <= '9')
		i++;
	if (str[i] == '+' && str[i + 1] >= '0' && str[i + 1] <= '9')
		i++;
	while (str[i])
	{
		if (str[0] >= '0' && str[0] <= '9')
			i++;
		else if ((str[i] >= '0' && str[i] <= '9'))
			i++;
		else if ((str[i] >= 'a' && str[i] <= 'f')
			|| (str[i] >= 'A' && str[i] <= 'F'))
			i++;
		else
			return (1);
	}
	return (0);
}

int	check_line(char *str)
{
	int		i;
	char	**data;

	data = ft_split(str, ' ');
	i = 0;
	while (data[i])
	{
		if (ft_check_atoi(data[i]) == 1)
		{
			ft_free_tab_c(data);
			return (1);
		}
		else
			i++;
	}
	ft_free_tab_c(data);
	return (0);
}
