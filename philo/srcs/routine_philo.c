/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 16:16:39 by barodrig          #+#    #+#             */
/*   Updated: 2022/05/06 14:59:42 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	meal_nbr_update(t_philo *philo)
{
	t_data *data;

	data = philo->data;
	pthread_mutex_lock(data->mutex_meal);
	if (philo->meal_nbr == data->tm_need_eat)
		data->tot_meals++;
	pthread_mutex_unlock(data->mutex_meal);
}

void	philo_cycle(t_philo *philo)
{
	t_data *data;
	
	data = philo->data;
	pthread_mutex_lock(&data->mutex_fork[philo->right]);
	printer(philo, philo->id, "has taken a fork");
	pthread_mutex_lock(&data->mutex_fork[philo->left]);
	printer(philo, philo->id, "has taken a fork");
	printer(philo, philo->id, "is eating");
	pthread_mutex_lock(philo->meal_lock);
	philo->tm_last_meal = time_is();
	pthread_mutex_unlock(philo->meal_lock);
	meal_nbr_update(philo);
	sleep_opti(data->tmt_eat);
	pthread_mutex_unlock(&data->mutex_fork[philo->right]);
	pthread_mutex_unlock(&data->mutex_fork[philo->left]);
	printer(philo, philo->id, "is sleeping");
	sleep_opti(data->tmt_sleep);
	printer(philo, philo->id, "is thinking");
	
}

int	must_philo_stop(t_philo *philo)
{
	pthread_mutex_lock(philo->data->mutex_dead);
	pthread_mutex_lock(philo->data->mutex_meal);
	if ((philo->data->tm_need_eat != -1 && philo->data->philo_nbr \
			== philo->data->tot_meals) || philo->data->one_dead)
	{
		pthread_mutex_unlock(philo->data->mutex_dead);
		pthread_mutex_unlock(philo->data->mutex_meal);
		return (1);
	}
	pthread_mutex_unlock(philo->data->mutex_dead);
	pthread_mutex_unlock(philo->data->mutex_meal);
	return (0);
}

void	*philo_routine(void *p_data)
{
	t_philo	*philo;

	philo = (t_philo *)p_data;
	pthread_create(philo->monitor, NULL, &monitor_routine, philo);
	if (philo->data->philo_nbr == 1)
	{
		printf("%li 1 has taken a fork\n", time_is() - philo->data->tm_start);
		return (NULL);
	}
	while (1)
	{
		if (must_philo_stop(philo))
			return (NULL);
		philo_cycle(philo);
	}
	return (NULL);
}