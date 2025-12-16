/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:24:31 by mouerchi          #+#    #+#             */
/*   Updated: 2024/11/05 11:08:40 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibc.h"

char	*ft_strrchr(const char *str, int c)
{
	size_t		i;

	if (!(*str))
	{
		if (c == 0)
			return ((char *)str);
		return (0);
	}
	i = ft_strlen(str);
	while (i > 0 && str[i] != (char)c)
		i--;
	if (str[i] == (char)c)
		return ((char *)(str + i));
	return (NULL);
}
