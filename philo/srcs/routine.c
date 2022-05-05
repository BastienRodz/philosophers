/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 16:16:39 by barodrig          #+#    #+#             */
/*   Updated: 2022/05/05 16:22:31 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *p_data)
{
	t_philo	*philo;

	philo = (t_philo *)p_data;
	printf("The time since philo[%i] started is %li\n", philo->id, time_is());
	return (NULL);
}
