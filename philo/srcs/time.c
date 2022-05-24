/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 14:41:49 by barodrig          #+#    #+#             */
/*   Updated: 2022/05/24 14:28:04 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	time_is(void)
{
	struct timeval	time;
	long int		time_conv_ms;

	gettimeofday(&time, NULL);
	time_conv_ms = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (time_conv_ms);
}

void	sleep_opti(long int sleep_time)
{
	long int	start;

	start = time_is();
	while ((time_is() - start) < sleep_time)
		usleep(sleep_time / 10);
}
