/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:55:32 by mouerchi          #+#    #+#             */
/*   Updated: 2025/01/11 09:24:21 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibc.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (size != 0 && count > __SIZE_MAX__ / size)
		return (NULL);
	ptr = malloc((size * count));
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
}
