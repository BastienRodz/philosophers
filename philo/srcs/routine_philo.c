/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 16:16:39 by barodrig          #+#    #+#             */
/*   Updated: 2022/05/06 13:16:19 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	must_philo_stop(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_dead);
	pthread_mutex_lock(&philo->data->mutex_meal);
	if ((philo->data->tm_need_eat != -1 && \
		philo->meal_nbr == philo->data->tm_need_eat) || philo->data->one_dead)
	{
		pthread_mutex_unlock(&philo->data->mutex_dead);
		pthread_mutex_unlock(&philo->data->mutex_meal);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->mutex_dead);
	pthread_mutex_unlock(&philo->data->mutex_meal);
	return (0);
}

void	*philo_routine(void *p_data)
{
	t_philo	*philo;

	philo = (t_philo *)p_data;
	if (pthread_create(&philo->monitor, NULL, &monitor_routine, philo))
		return(ft_putstr_fd("Failed to create a monitor thread.", 2));
	if (philo->data->philo_nbr == 1)
	{
		printf("%li 1 has taken a fork\n", time_is() - philo->data->tm_start);
		return (NULL);
	}
	while (1)
	{
		if (must_philo_stop(philo))
			return (NULL);
		//philo_cycle(philo);
	}
	printf("The time since philo[%i] started is %li\n", philo->id, time_from_start(philo->data));
	return (NULL);
}
