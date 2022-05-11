/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 16:16:39 by barodrig          #+#    #+#             */
/*   Updated: 2022/05/11 10:09:28 by barodrig         ###   ########.fr       */
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

void	launch_even_philo(t_data *data, t_philo *philo)
{
	if (philo->id % 2 == 0)
		return ;
	else
		sleep_opti(data->tmt_eat / 10);
	return ;
}

void	launch_odd_philo(t_data *data, t_philo *philo)
{
	if (philo->id % 3 == 0)
		return ;
	else if (philo->id + 1 % 3 == 0)
		usleep(data->tmt_eat / 300);
	else
		usleep(data->tmt_eat / 200);
}

void	*philo_routine(void *p_data)
{
	t_philo	*philo;

	philo = (t_philo *)p_data;
	pthread_mutex_lock(philo->data->mutex_init);
	pthread_mutex_unlock(philo->data->mutex_init);
	if (philo->data->philo_nbr % 2 == 0)
	 	launch_even_philo(philo->data, philo);
	else
		launch_odd_philo(philo->data, philo);
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
		sleep_opti(philo->data->tmt_eat/800);
	}
	return (NULL);
}