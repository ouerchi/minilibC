/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:16:03 by mouerchi          #+#    #+#             */
/*   Updated: 2024/11/05 11:27:30 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibc.h"

void	*ft_memset(void *str, int value, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		((unsigned char *)str)[i] = (unsigned char)value;
		i++;
	}
	return (str);
}
