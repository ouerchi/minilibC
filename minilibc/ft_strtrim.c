/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 17:15:40 by mouerchi          #+#    #+#             */
/*   Updated: 2024/11/07 10:10:48 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibc.h"

static int	set_check(char const *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	char	*new;

	if (!s1 || !set)
		return (NULL);
	while (*s1)
	{
		if (!set_check(set, *s1))
			break ;
		s1++;
	}
	len = ft_strlen(s1);
	while (len != 0)
	{
		if (set_check(set, s1[len - 1]))
			len--;
		else
			break ;
	}
	new = (char *)malloc(len + 1);
	if (!new)
		return (NULL);
	ft_strlcpy(new, s1, len + 1);
	return (new);
}
