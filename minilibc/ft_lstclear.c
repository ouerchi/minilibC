/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 13:44:59 by mouerchi          #+#    #+#             */
/*   Updated: 2025/01/11 15:40:57 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibc.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		(*del)((*lst)->content);
		tmp = (*lst)->next;
		free(*lst);
		(*lst) = tmp;
	}
	*lst = NULL;
}
