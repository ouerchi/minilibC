/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 12:53:55 by mouerchi          #+#    #+#             */
/*   Updated: 2024/11/07 09:22:16 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibc.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*str;
	size_t			length;
	size_t			i;

	if (!s || !f)
		return (NULL);
	i = 0;
	length = ft_strlen(s);
	str = (char *)malloc(length + 1);
	if (!str)
		return (NULL);
	while (i < length)
	{
		str[i] = (*f)(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}
