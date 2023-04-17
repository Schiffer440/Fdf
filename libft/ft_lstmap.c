/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adugain <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:35:44 by adugain           #+#    #+#             */
/*   Updated: 2022/11/30 19:47:29 by adugain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*nnew;

	nnew = 0;
	while (lst)
	{
		new = ft_lstnew((*f)(lst->content));
		if (!new)
		{
			ft_lstclear(&nnew, del);
			return (0);
		}
		ft_lstadd_back(&nnew, new);
		lst = lst->next;
	}
	return (nnew);
}
