/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adugain <adugain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:53:46 by adugain           #+#    #+#             */
/*   Updated: 2023/05/16 16:54:50 by adugain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int     ft_abs(int nb)
{
        return (nb < 0 ? nb * -1 : nb);
}