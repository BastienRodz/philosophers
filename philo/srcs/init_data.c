/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 16:55:48 by barodrig          #+#    #+#             */
/*   Updated: 2022/05/05 16:11:22 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_mutex_ready(t_data *data)
{
	int	i;

	i = -1;
	if (pthread_mutex_init(data->mutex_print, NULL))
		return (ft_putstr_fd("Mutex initialization failed", 2));
	if (pthread_mutex_init(data->mutex_dead, NULL))
		return (ft_putstr_fd("Mutex initialization failed", 2));
	if (pthread_mutex_init(data->mutex_meal, NULL))
		return (ft_putstr_fd("Mutex initialization failed", 2));
	while (++i < data->philo_nbr)
	{
		if (pthread_mutex_init(&data->mutex_fork[i], NULL))
			return (ft_putstr_fd("Mutex initialization failed", 2));
	}
	return (0);
}

int	init_data_mutex(t_data *data)
{
	data->mutex_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* data->philo_nbr);
	if (!data->mutex_fork)
		return (1);
	data->mutex_meal = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!data->mutex_meal)
		return (1);
	data->mutex_print = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!data->mutex_print)
		return (1);
	data->mutex_dead = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!data->mutex_dead)
		return (1);
	return (0);
}

int	data_init(t_data *data, char **av)
{
	data->philo_nbr = ft_atoi(av[1]);
	data->tmt_die = ft_atoi(av[2]);
	data->tmt_eat = ft_atoi(av[3]);
	data->tmt_sleep = ft_atoi(av[4]);
	data->tm_start = time_is();
	data->one_dead = 0;
	if (av[5])
		data->tm_need_eat = ft_atoi(av[5]);
	else
		data->tm_need_eat = -1;
	data->philos = malloc(sizeof(t_philo) * data->philo_nbr);
	if (!data->philos)
		return (1);
	data->philo_th = (pthread_t *)malloc(sizeof(pthread_t)
			* data->philo_nbr);
	if (!data->philo_th)
		return (1);
	if (init_data_mutex(data))
		return (1);
	return (0);
}
