/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 16:07:27 by barodrig          #+#    #+#             */
/*   Updated: 2022/05/05 13:57:50 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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