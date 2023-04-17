/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adugain <adugain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 11:57:23 by adugain           #+#    #+#             */
/*   Updated: 2023/03/13 13:55:29 by adugain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putchar(char c, int *len)
{
	*len += write(1, &c, 1);
}

static void	ft_putnbr_base(long int nbr, char *base, int *len)
{
	int	i;

	i = 0;
	while (base[i])
		i++;
	if (nbr < 0)
	{
		ft_putchar('-', len);
		nbr = -nbr;
	}
	if (nbr / i)
		ft_putnbr_base(nbr / i, base, len);
	ft_putchar(base[nbr % i], len);
}

static void	ft_putstr(char *str, int *len)
{
	int	i;

	i = 0;
	if (!str)
	{
		ft_putstr("(null)", len);
		return ;
	}
	while (str[i])
	{
		*len += write(1, &str[i], 1);
		i++;
	}
}

static void	ft_putptr(unsigned long int nbr, char *base, int *len, int token)
{
	int	i;

	i = 0;
	if (!nbr)
	{
		ft_putstr("(nil)", len);
		return ;
	}
	if (token == 1)
		ft_putstr("0x", len);
	while (base[i])
		i++;
	if (nbr / i)
		ft_putptr(nbr / i, base, len, 0);
	ft_putchar(base[nbr % i], len);
}

int	format(char c, va_list args)
{
	int	len;

	len = 0;
	if (c == 'c')
		ft_putchar(va_arg(args, int), &len);
	else if (c == 's')
		ft_putstr(va_arg(args, char *), &len);
	else if (c == 'd' || c == 'i')
		ft_putnbr_base(va_arg(args, int), "0123456789", &len);
	else if (c == 'u')
		ft_putnbr_base(va_arg(args, unsigned int), "0123456789", &len);
	else if (c == 'x')
		ft_putnbr_base(va_arg(args, unsigned int), "0123456789abcdef", &len);
	else if (c == 'X')
		ft_putnbr_base(va_arg(args, unsigned int), "0123456789ABCDEF", &len);
	else if (c == 'p')
		ft_putptr(va_arg(args, unsigned long int), "0123456789abcdef", &len, 1);
	else if (c == '%')
		ft_putchar('%', &len);
	else
		return (len = -1);
	return (len);
}
