/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 16:07:27 by barodrig          #+#    #+#             */
/*   Updated: 2022/05/06 13:27:49 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    printer(t_philo *philo, int id, char *str)
{
    long int    time;

    time = 0;
    pthread_mutex_lock(&philo->data->mutex_meal);
    pthread_mutex_lock(&philo->data->mutex_dead);
    if (philo->data->tm_need_eat != philo->meal_nbr && !philo->data->one_dead)
    {
        
    }
}

int ft_putstr_fd(char *str, int fd)
{
    int i;
    
    i = -1;
    if (!str || !str[0])
        return (1);
    while (str[++i])
    {
        write(fd, &str[i], 1);
    }
    write(fd, "\n", 1);
    return (1);
}