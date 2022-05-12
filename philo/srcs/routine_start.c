/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_start.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 10:03:29 by barodrig          #+#    #+#             */
/*   Updated: 2022/05/12 16:22:10 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	philo->tm_last_meal = time_is();
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
		if (philo_cycle(philo))
			return (NULL);
		sleep_opti(philo->data->tmt_think / philo->data->tmt_die);
	}
	return (NULL);
}