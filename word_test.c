/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adugain <adugain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 09:20:55 by adugain           #+#    #+#             */
/*   Updated: 2023/04/28 15:01:22 by adugain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

int	encode_rgb(u_int8_t red, u_int8_t green, u_int8_t blue)
{
	return (red << 16 | green << 8 | blue);
}

int main()
{
	int	o = 0x0a;
	//o += 16;
	printf("word:%d\n", o);
}