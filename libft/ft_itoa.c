/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 09:31:21 by mouerchi          #+#    #+#             */
/*   Updated: 2024/11/06 09:49:28 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_int(int n)
{
	size_t	i;

	i = 0;
	if (n < 0)
	{
		i++;
		n *= -1;
	}
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	size_t	len_n;
	char	*str;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len_n = count_int(n);
	str = (char *)ft_calloc(len_n + 1, sizeof(char));
	if (!str)
		return (NULL);
	if (n < 0)
	{
		str[0] = '-';
		n *= -1;
	}
	if (n == 0)
		str[len_n - 1] = 0 + '0';
	while (n > 0)
	{
		str[len_n - 1] = (n % 10) + '0';
		n /= 10;
		len_n--;
	}
	return (str);
}
