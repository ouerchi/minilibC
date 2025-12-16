/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 20:35:19 by mouerchi          #+#    #+#             */
/*   Updated: 2024/11/06 17:05:58 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibc.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}
