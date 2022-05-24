/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 16:47:36 by barodrig          #+#    #+#             */
/*   Updated: 2022/05/24 15:00:33 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	are_digits(char *str)
{
	int	flag;
	int	i;

	flag = 0;
	i = -1;

	while (str[++i])
		if (str[i] < 48 || str[i] > 57)
			flag = 1;
	return (flag);
}

int	ft_atoi(const char *str)
{
	long long int	res;
	long long int	sign;

	res = 0;
	sign = 1;
	while (*str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\f' || *str == '\r' || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -sign;
		str++;
	}
	while (*str && (*str >= '0' && *str <= '9'))
	{
		res = res * 10 + (*str - 48);
		str++;
	}
	return ((int)(res * sign));
}
