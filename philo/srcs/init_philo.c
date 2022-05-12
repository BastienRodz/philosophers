/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 16:11:42 by barodrig          #+#    #+#             */
/*   Updated: 2022/05/12 16:33:03 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philos_pthread(t_data *data, int i)
{
	data->philos[i].meal_lock = malloc(sizeof(pthread_mutex_t) \
			* data->philo_nbr);
	if (!data->philos[i].meal_lock)
		return (ft_putstr_fd("Malloc error.", 2));
	if (pthread_mutex_init(data->philos[i].meal_lock, NULL))
		return (ft_putstr_fd("Meal_lock mutex init error.", 2));
	return (0);
}

int	create_philo_threads(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_nbr)
	{
		data->philos[i].id = i;
		data->philos[i].meal_nbr = 0;
		data->philos[i].data = data;
		data->philos[i].tm_last_meal = time_is();
		data->philos[i].stop = 0;
		//Modified
		if (!(i + 1 % data->philo_nbr))
		{
			data->philos[i].right = data->philos[i].id;
			data->philos[i].left = (data->philos[i].id + 1) % data->philo_nbr;
		}
		else
		{
			data->philos[i].left = data->philos[i].id;
			data->philos[i].right = (data->philos[i].id + 1) % data->philo_nbr;
		}
		if (init_philos_pthread(data, i))
			return (1);
	}
	return (0);
}
