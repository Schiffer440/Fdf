/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adugain <adugain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 15:25:10 by adugain           #+#    #+#             */
/*   Updated: 2023/07/22 12:17:16 by adugain          ###   ########.fr       */
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
