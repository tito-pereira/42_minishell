/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 12:46:33 by tibarbos          #+#    #+#             */
/*   Updated: 2024/05/11 10:27:31 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*nlist;
	t_list	*new;

	if (f == NULL || lst == NULL || del == NULL)
		return (NULL);
	new = ft_lstnew(f(lst->content));
	if (new == NULL)
		ft_lstdelone(lst->content, del);
	nlist = new;
	lst = lst->next;
	while (lst != NULL)
	{
		new = ft_lstnew(f(lst->content));
		if (new == NULL)
			ft_lstdelone(lst->content, del);
		ft_lstadd_back(&nlist, new);
		lst = lst->next;
	}
	return (nlist);
}
