/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:53:39 by mouerchi          #+#    #+#             */
/*   Updated: 2024/11/06 09:08:37 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibc.h"

static int	check_sign(int sign)
{
	if (sign < 0)
		return (0);
	else
		return (-1);
}

int	ft_atoi(const char *str)
{
	long long	result;
	long long	old_result;
	int			sign;
	int			i;

	result = 0;
	sign = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		old_result = result;
		result = result * 10 + (sign * (str[i] - '0'));
		if ((result / 10) != old_result)
			return (check_sign(sign));
		i++;
	}
	return (result);
}
