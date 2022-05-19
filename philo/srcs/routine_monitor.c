/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_monitor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 13:12:27 by barodrig          #+#    #+#             */
/*   Updated: 2022/05/19 03:07:39 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	monitor_update_meal(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(data->mutex_meal);
	if (data->tot_meals == data->philo_nbr && data->tm_need_eat != -1)
	{
		pthread_mutex_unlock(data->mutex_meal);
		pthread_mutex_lock(data->mutex_dead);
		data->one_dead = 1;
		pthread_mutex_unlock(data->mutex_dead);
		return (1);
	}
	pthread_mutex_unlock(data->mutex_meal);
	return (0);
}

int	check_for_dead_philo(t_philo *philo)
{
	t_data		*data;
	long int	lst_meal;

	data = philo->data;
	pthread_mutex_lock(philo->meal_lock);
	lst_meal = philo->tm_last_meal;
	pthread_mutex_unlock(philo->meal_lock);
	if (time_is() - lst_meal > data->tmt_die)
	{
		printer(philo, philo->id, "died");
		pthread_mutex_lock(data->mutex_dead);
		data->one_dead = 1;
		pthread_mutex_unlock(data->mutex_dead);
		return (1);
	}
	if (monitor_update_meal(philo))
		return (1);
	return (0);
}

void	*monitor_routine(void *p_data)
{
	t_philo	*philo;

	philo = (t_philo *)p_data;
	while (1)
	{
		if (check_for_dead_philo(philo))
			return (NULL);
		usleep(200);
	}
	return (NULL);
}
