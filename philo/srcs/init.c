/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 16:55:48 by barodrig          #+#    #+#             */
/*   Updated: 2022/05/04 17:21:19 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_data_mutex(t_data *data)
{
	data->mutex_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* data->philo_nbr);
	if (!data->mutex_fork)
		return ;
	data->mutex_meal = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!data->mutex_meal)
		return ;
	data->mutex_print = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!data->mutex_print)
		return ;
	data->mutex_dead = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!data->mutex_dead)
		return ;
}

void	data_init(t_data *data, char **av)
{
	data->philo_nbr = ft_atoi(av[1]);
	data->tmt_die = ft_atoi(av[2]);
	data->tmt_eat = ft_atoi(av[3]);
	data->tmt_sleep = ft_atoi(av[4]);
	data->tm_start = 0;
	data->one_dead = 0;
	if (av[5])
		data->tm_need_eat = ft_atoi(av[6]);
	else
		data->tm_need_eat = -1;
	data->philos = (t_philo *)malloc(sizeof(t_philo) * data->philo_nbr);
	if (!data->philos)
		return ;
	data->philo_alive = (pthread_t *)malloc(sizeof(pthread_t)
			* data->philo_nbr);
	if (!data->philo_alive)
		return ;
	init_data_mutex(data);
	return ;
}
