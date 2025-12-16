/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 19:23:25 by mouerchi          #+#    #+#             */
/*   Updated: 2024/11/05 21:06:40 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibc.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	little_len;
	size_t	i;
	size_t	j;

	if (!big && !len && little)
		return (NULL);
	i = 0;
	if (little[i] == '\0')
		return ((char *)big);
	little_len = ft_strlen(little);
	while (big[i] && i < len)
	{
		j = 0;
		while (big[i + j] && big[i + j] == little[j] && i + j < len)
			j++;
		if (j == little_len)
			return ((char *)big + i);
		i++;
	}
	return (NULL);
}
