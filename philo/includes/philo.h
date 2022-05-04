/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 16:03:43 by barodrig          #+#    #+#             */
/*   Updated: 2022/05/04 18:32:53 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>

//Struct that carry all the args every philo needs;
typedef struct s_data
{
	long int			philo_nbr;
	long int			tmt_die;
	long int			tmt_eat;
	long int			tmt_sleep;
	long int			tm_need_eat;
	int					one_dead;
	int					tm_start;    
	struct t_philo		*philos;
	pthread_t			*philo_alive;
	pthread_mutex_t		*mutex_fork;
	pthread_mutex_t		*mutex_print;
	pthread_mutex_t		*mutex_dead;
	pthread_mutex_t		*mutex_meal;
}              			t_data;

// Struct that carry all the datas about one philo;
typedef struct s_philo
{
	int     			id;
	int					meal_nbr;
	int					tm_last_meal;
	int					left;
	int					right;
	pthread_t 			philo;
	struct t_data		*data;
}               		t_philo;


/* PRINT */
int 	ft_putstr_fd(char *str, int fd);

/* UTILS */
int		ft_atoi(const char *str);

/* INIT */
void    data_init(t_data *data, char **ac)


#endif