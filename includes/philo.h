/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 17:29:28 by barodrig          #+#    #+#             */
/*   Updated: 2022/03/19 18:14:41 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "unistd.h"
# include "pthread.h"
# include "stdio.h"
# include "stdlib.h"
# include "sys/time.h"

typedef struct s_philo
{
	int	nb_philo;
	int	no_philo;
	int	
}				t_philo;

int		is_arg_digit(char *str);
void	ft_putstr(char *s);

#endif