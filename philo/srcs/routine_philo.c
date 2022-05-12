/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 16:16:39 by barodrig          #+#    #+#             */
/*   Updated: 2022/05/12 16:06:00 by barodrig         ###   ########.fr       */
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

int		check_meal(t_philo *philo)
{
	int	flag;
	int	i;
	pthread_mutex_lock(philo->data->mutex_meal);
	if (philo->data->tm_need_eat != -1 && philo->data->tot_meals > 0)
	{
		pthread_mutex_unlock(philo->data->mutex_meal);
		flag = 1;
		i = -1;
		pthread_mutex_lock(philo->data->mutex_meal);
		while (++i < philo->data->philo_nbr)
			if (philo->data->philos[i].meal_nbr < philo->data->tot_meals)
				flag = 0;
		pthread_mutex_unlock(philo->data->mutex_meal);
		if (flag)
		{
			i = -1;
			pthread_mutex_lock(philo->data->mutex_print);
			while (++i < philo->data->philo_nbr)
				philo->data->philos[i].stop = 1;
			pthread_mutex_unlock(philo->data->mutex_print);
			return (1);
		}
	}
	pthread_mutex_unlock(philo->data->mutex_meal);
	return (0);
}

int	check_stop(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(data->mutex_dead);
	if (data->one_dead || philo->stop || check_meal(philo))
	{
		pthread_mutex_unlock(data->mutex_dead);
		return (1);
	}
	pthread_mutex_unlock(data->mutex_dead);
	return (0);
}

int	philo_cycle(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (check_stop(data, philo))
		return (1);
	pthread_mutex_lock(&data->mutex_fork[philo->right]);
	printer(philo, philo->id, "has taken a fork");
	pthread_mutex_lock(&data->mutex_fork[philo->left]);
	printer(philo, philo->id, "has taken a fork");
	if (check_stop(data, philo))
		return (1);
	printer(philo, philo->id, "is eating");
	pthread_mutex_lock(philo->meal_lock);
	philo->tm_last_meal = time_is();
	pthread_mutex_unlock(philo->meal_lock);
	meal_nbr_update(philo);
	sleep_opti(data->tmt_eat);
	pthread_mutex_unlock(&data->mutex_fork[philo->right]);
	pthread_mutex_unlock(&data->mutex_fork[philo->left]);
	if (check_stop(data, philo))
		return (1);
	printer(philo, philo->id, "is sleeping");
	sleep_opti(data->tmt_sleep);
	if (check_stop(data, philo))
		return (1);
	printer(philo, philo->id, "is thinking");
	return (0);
}