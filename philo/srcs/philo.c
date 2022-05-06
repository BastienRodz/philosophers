/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 16:01:44 by barodrig          #+#    #+#             */
/*   Updated: 2022/05/06 22:07:26 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	wait_for_threads(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_nbr - 1)
	{
		if (pthread_join(data->philo_th[i], NULL))
			return (ft_putstr_fd("Error while joining a thread.(philo_th)", 2));
		if (pthread_join(*data->philos[i].monitor, NULL))
			return (ft_putstr_fd("Error while joining a thread.(monitor)", 2));
	}
	return (0);
}

int	set_threads(char **av, t_data *data)
{
	int	i;

	i = -1;
	if (!data)
		return (ft_putstr_fd("Struct 'data' malloc error.", 2));
	if (data_init(data, av))
		return (ft_putstr_fd("Init in struct 'data' error.", 2));
	if (get_mutex_ready(data))
		return (1);
	if (create_philo_threads(data))
		return (1);
	while (++i < data->philo_nbr)
	{
		if ((i % 2) == 0)
			sleep_opti(data->tm_need_eat * 0.9);
		if (pthread_create(&data->philo_th[i], NULL, \
					&philo_routine, (void *)&data->philos[i]))
			return (ft_putstr_fd("Failed to create a philo thread.", 2));
	}
	if (wait_for_threads(data))
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	int		i;
	t_data	*data;

	i = 0;
	data = (t_data *)malloc(sizeof(t_data));
	if (ac < 5 || ac > 6)
		return (ft_putstr_fd("Wrong number of arguments (5 or 6 needed).", 2));
	while (++i < ac)
	{
		if (ft_atoi(av[i]) < 0)
			return (ft_putstr_fd("Arguments can't be negatives numbers.", 2));
	}
	if (set_threads(av, data))
		return (_exit_philo(data), 1);
	_exit_philo(data);
}
