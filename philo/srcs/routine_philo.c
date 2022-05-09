/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 16:16:39 by barodrig          #+#    #+#             */
/*   Updated: 2022/05/09 19:43:48 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	meal_nbr_update(t_philo *philo)
{
	pthread_mutex_lock(philo->data->mutex_meal);
	philo->meal_nbr++;
	if (philo->meal_nbr == philo->data->tm_need_eat)
		philo->data->tot_meals++;
	pthread_mutex_unlock(philo->data->mutex_meal);
}

void	philo_cycle(t_philo *philo)
{
	t_data	*data;

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
	//sleep_opti(data->tmt_eat / 2);
}

int	must_philo_stop(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(data->mutex_dead);
	if (data->one_dead)
	{
		pthread_mutex_unlock(data->mutex_dead);
		return (1);
	}
	pthread_mutex_unlock(data->mutex_dead);
	pthread_mutex_lock(data->mutex_meal);
	if (data->tm_need_eat != -1 && (data->philo_nbr == data->tot_meals))
	{
		pthread_mutex_unlock(data->mutex_meal);
		return (1);
	}
	pthread_mutex_unlock(data->mutex_meal);
	return (0);
}

void	*philo_routine(void *p_data)
{
	t_philo	*philo;

	philo = (t_philo *)p_data;
	pthread_mutex_lock(philo->data->mutex_init);
	pthread_mutex_unlock(philo->data->mutex_init);
	if (philo->id % 2 != 0)
		sleep_opti(5);
	if (philo->data->philo_nbr == 1)
	{
		printer(philo, philo->id, "has taken a fork");
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
