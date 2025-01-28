/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 21:11:31 by mouerchi          #+#    #+#             */
/*   Updated: 2024/11/04 15:49:00 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub_str;
	size_t	src_len;
	size_t	i;

	if (!s)
		return (NULL);
	src_len = ft_strlen(s);
	if (start <= src_len)
		i = src_len - start;
	if (start > src_len)
		return ((char *)ft_calloc(1, 1));
	if (i > len)
		i = len;
	sub_str = (char *)malloc((i + 1) * sizeof(char));
	if (!sub_str)
		return (NULL);
	ft_strlcpy(sub_str, s + start, i + 1);
	return (sub_str);
}
