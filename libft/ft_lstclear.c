/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adugain <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 15:25:10 by adugain           #+#    #+#             */
/*   Updated: 2022/11/30 16:46:44 by adugain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*s;

	if (lst && del)
	{
		while (*lst)
		{
			s = (*lst)->next;
			ft_lstdelone(*lst, del);
			*lst = s;
		}
	*lst = 0;
	}
}
