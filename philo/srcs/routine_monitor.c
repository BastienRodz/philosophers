/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_monitor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 13:12:27 by barodrig          #+#    #+#             */
/*   Updated: 2022/05/12 16:13:32 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_i_died(t_philo *philo, t_data *data, int i)
{
	printer(philo, philo->id, "died");
	pthread_mutex_lock(data->mutex_dead);
	pthread_mutex_lock(data->mutex_print);
	data->one_dead = 1;
	i = -1;
	while (++i < data->philo_nbr)
		data->philos[i].stop = 1;
	pthread_mutex_unlock(data->mutex_dead);
	pthread_mutex_unlock(data->mutex_print);
}

void	*monitor_routine(void *p_data)
{
	t_data 		*data;
	int			i;

	data = (t_data *)p_data;
	pthread_mutex_lock(data->mutex_init);
	pthread_mutex_unlock(data->mutex_init);
	while (1)
	{
		i = -1;
		while (++i < data->philo_nbr)
		{
			pthread_mutex_lock(data->mutex_dead);
			if (data->one_dead || data->philos[i].stop)
			{
				pthread_mutex_unlock(data->mutex_dead);
				return (NULL);
			}
			pthread_mutex_unlock(data->mutex_dead);
			pthread_mutex_lock(data->philos[i].meal_lock);
			if (time_is() - data->philos[i].tm_last_meal > data->tmt_die)
			{
				philo_i_died(&data->philos[i], data, i);
				pthread_mutex_unlock(data->philos[i].meal_lock);
				return (NULL);
			}
			pthread_mutex_unlock(data->philos[i].meal_lock);
			if (check_meal(&data->philos[i]) || data->philos[i].stop)
				return (NULL);
		}
		sleep_opti(5);
	}
	return (NULL);
}
