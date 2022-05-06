/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 16:07:27 by barodrig          #+#    #+#             */
/*   Updated: 2022/05/06 18:12:03 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	printer(t_philo *philo, int id, char *str)
{
	long int	time;

	time = 0;
	pthread_mutex_lock(philo->data->mutex_dead);
	pthread_mutex_lock(philo->data->mutex_meal);
	if (philo->data->tm_need_eat != philo->data->tot_meals \
			&& !philo->data->one_dead)
	{
		pthread_mutex_lock(philo->data->mutex_print);
		time = time_is() - philo->data->tm_start;
		printf("%li %i %s\n", time, id + 1, str);
		pthread_mutex_unlock(philo->data->mutex_print);
	}
	pthread_mutex_unlock(philo->data->mutex_dead);
	pthread_mutex_unlock(philo->data->mutex_meal);
}

int	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = -1;
	if (!str || !str[0])
		return (1);
	while (str[++i])
	{
		write(fd, &str[i], 1);
	}
	write(fd, "\n", 1);
	return (1);
}
