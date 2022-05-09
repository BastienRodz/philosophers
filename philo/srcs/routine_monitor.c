/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_monitor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 13:12:27 by barodrig          #+#    #+#             */
/*   Updated: 2022/05/09 19:26:43 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	monitor_update_meal(t_data *data)
{
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

int	check_for_dead_philo(t_data *data, int i)
{
	long int	lst_meal;

	pthread_mutex_lock(data->philos[i].meal_lock);
	lst_meal = data->philos[i].tm_last_meal;
	pthread_mutex_unlock(data->philos[i].meal_lock);
	if (time_is() - lst_meal > data->tmt_die)
	{
		printer(&data->philos[i], data->philos[i].id, "died");
		pthread_mutex_lock(data->mutex_dead);
		pthread_mutex_lock(data->mutex_print);
		data->one_dead = 1;
		pthread_mutex_unlock(data->mutex_print);
		pthread_mutex_unlock(data->mutex_dead);
		return (1);
	}
	if (monitor_update_meal(data))
		return (1);
	return (0);
}

void	*monitor_routine(void *p_data)
{
	t_data *data;
	int	i;

	data = (t_data *)p_data;
	pthread_mutex_lock(data->mutex_init);
	pthread_mutex_unlock(data->mutex_init);
	while (1)
	{
		i = -1;
		while (++i < data->philo_nbr)
		{
			if (check_for_dead_philo(data, i))
				return (NULL);
		}
		sleep_opti(2);
	}
	return (NULL);
}
