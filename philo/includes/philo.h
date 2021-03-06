/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 16:03:43 by barodrig          #+#    #+#             */
/*   Updated: 2022/05/24 15:02:03 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <time.h>

struct	s_philo;
struct	s_data;

typedef struct s_philo
{
	int					id;
	int					meal_nbr;
	long int			tm_last_meal;
	int					left;	
	int					right;
	pthread_mutex_t		*meal_lock;
	struct s_data		*data;
}						t_philo;

typedef struct s_data
{
	long int			philo_nbr;
	long int			tmt_die;
	long int			tmt_eat;
	long int			tmt_sleep;
	long int			tm_need_eat;
	long int			one_dead;
	long int			tm_start;
	long int			tot_meals;
	t_philo				*philos;
	pthread_t			*philo_th;
	pthread_t			*monitor;
	pthread_mutex_t		*mutex_fork;
	pthread_mutex_t		*mutex_print;
	pthread_mutex_t		*mutex_dead;
	pthread_mutex_t		*mutex_meal;
}						t_data;

/* ROUTINE MONITOR */
void		*monitor_routine(void *p_data);

/* ROUTINE PHILO*/
void		*philo_routine(void *p_data);

/* PRINT */
int			ft_putstr_fd(char *str, int fd);
void		printer(t_philo *philo, int id, char *str);

/* TIME */
long int	time_is(void);
void		sleep_opti(long int sleep_time);

/* UTILS */
int			ft_atoi(const char *str);
int			are_digits(char *str);

/* FREE */
int			_exit_philo(t_data *data);

/* INIT */
int			data_init(t_data *data, char **av);
int			create_philo_threads(t_data *data);
int			get_mutex_ready(t_data *data);

#endif