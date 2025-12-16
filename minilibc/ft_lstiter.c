/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 15:27:03 by mouerchi          #+#    #+#             */
/*   Updated: 2024/11/04 16:50:21 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibc.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		(*f)(lst->content);
		lst = lst->next;
	}
}
