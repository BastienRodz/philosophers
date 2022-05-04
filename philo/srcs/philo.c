/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 16:01:44 by barodrig          #+#    #+#             */
/*   Updated: 2022/05/04 16:55:46 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    *routine()
{
    printf("START prout\n");
    sleep(3);
    printf("lalala END\n");
    return (NULL);
}

void    set_threads(char **av, int philo_nbr)
{
    t_data *data;

    data = (t_data *)malloc(sizeof(t_data));
    if (!data)
        return (ft_putstr_fd("Data malloc error\n", 2));
    data_init(data, av);
    
}

int main(int ac, char **av)
{
    int i;

    i = 0;
    if (ac < 5 || ac > 6)
        return (ft_putstr_fd("Wrong number of arguments (5 or 6 needed).", 2));
    while (++i < ac)
    {
        if (ft_atoi(av[i]) < 0)
            return (ft_putstr_fd("Arguments can't be negatives numbers."), 2);
    }
    set_threads(av, ft_atoi(av[1]));
}