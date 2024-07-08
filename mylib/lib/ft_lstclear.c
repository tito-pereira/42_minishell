/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 12:45:37 by tibarbos          #+#    #+#             */
/*   Updated: 2024/05/11 10:26:55 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;

	while ((*lst) != NULL)
	{
		tmp = (*lst)->next;
		if (del != NULL)
			del((*lst)->content);
		free((*lst));
		(*lst) = tmp;
	}
}
