/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 14:15:37 by barodrig          #+#    #+#             */
/*   Updated: 2022/05/12 16:08:39 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all_philos(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_nbr)
	{
		pthread_mutex_destroy(data->philos[i].meal_lock);
		pthread_mutex_destroy(&data->mutex_fork[i]);
		if (data->philos[i].meal_lock)
			free(data->philos[i].meal_lock);
	}
}

int	_exit_philo(t_data *data)
{
	free_all_philos(data);
	pthread_mutex_destroy(data->mutex_dead);
	pthread_mutex_destroy(data->mutex_meal);
	pthread_mutex_destroy(data->mutex_print);
	pthread_mutex_destroy(data->mutex_init);
	if (data->philos)
		free(data->philos);
	if (data->philo_th)
		free(data->philo_th);
	if (data->mutex_print)
		free(data->mutex_print);
	if (data->mutex_dead)
		free(data->mutex_dead);
	if (data->mutex_meal)
		free(data->mutex_meal);
	if (data->mutex_fork)
		free(data->mutex_fork);
	if (data->mutex_init)
		free(data->mutex_init);
	if (data->monitor)
		free(data->monitor);
	free(data);
	return (0);
}
