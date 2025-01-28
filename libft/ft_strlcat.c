/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 10:40:53 by mouerchi          #+#    #+#             */
/*   Updated: 2024/11/01 13:32:45 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	ldst;
	size_t	lsrc;
	size_t	i;

	lsrc = ft_strlen(src);
	if (dstsize == 0 && !dst)
		return (lsrc);
	ldst = ft_strlen(dst);
	if (ldst >= dstsize)
		return (lsrc + dstsize);
	i = 0;
	while (src[i] && i + ldst < dstsize - 1)
	{
		dst[ldst + i] = src[i];
		i++;
	}
	dst[ldst + i] = '\0';
	return (ldst + lsrc);
}
