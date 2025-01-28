/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 12:55:17 by mouerchi          #+#    #+#             */
/*   Updated: 2025/01/11 19:53:05 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*new;
	size_t	lnew;

	if (!s1 && !s2)
		return (NULL);
	else if (!s1)
		return (ft_strdup(s2));
	else if (!s2)
		return (ft_strdup(s1));
	lnew = (ft_strlen(s1) + ft_strlen(s2)) + 1;
	new = (char *)malloc(lnew * sizeof(char));
	if (!new)
		return (NULL);
	ft_strlcpy(new, s1, lnew);
	ft_strlcat(new + ft_strlen(s1), s2, lnew);
	return (new);
}
