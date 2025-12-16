/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:54:55 by mouerchi          #+#    #+#             */
/*   Updated: 2024/11/06 11:53:10 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibc.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;

	i = 0;
	if ((unsigned char *)dst == (unsigned char *)src)
		return (dst);
	while (i < n)
	{
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dst);
}
