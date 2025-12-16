/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 19:30:05 by mouerchi          #+#    #+#             */
/*   Updated: 2025/01/11 20:08:44 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibc.h"

char	*ft_strdup(const char *src)
{
	char	*ptr;
	size_t	src_len;

	src_len = ft_strlen(src);
	ptr = (char *)malloc(src_len + 1);
	if (!ptr)
		return (NULL);
	ft_memcpy(ptr, src, src_len + 1);
	return (ptr);
}
