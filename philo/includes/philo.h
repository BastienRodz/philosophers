/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 16:03:43 by barodrig          #+#    #+#             */
/*   Updated: 2022/05/09 13:49:07 by barodrig         ###   ########.fr       */
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


// Struct that carry all the datas about one philo,
// it has a pointer to the data struct and is the arg passed at the threads' creation.
typedef struct s_philo
{
	int					id;				// The philo ID represents his position in the order his threads was launched.
	int					meal_nbr;		// The number of meal a philo has had.
	long int			tm_last_meal;	// The time of the last time a philo has begun to eat.
	int					left;			// The id of the philo owning the left fork.
	int					right;			// The id of the philo owning the right fork.
	pthread_mutex_t		*meal_lock;		// This mutex is locked everytime the "meal_nbr" variable is read of modified.
	pthread_t			*monitor;		// The monitor thread which is launched for each philo.
	struct s_data		*data;			// Pointer to the data struct.
}						t_philo;

// Struct that carry all the args every philo needs;
typedef struct s_data
{
	long int			philo_nbr;		// Total nbr of philosophers.
	long int			tmt_die;		// Time after which if a philo hasn't eaten he will die.
	long int			tmt_eat;		// Time that takes a philo to eat.
	long int			tmt_sleep;		// Time that sleeps a philo.
	long int			tm_need_eat;	// Time a philo need to eat before stopping (not dying).
	long int			one_dead;		// Initialize to 0, if a philo die it will be set to 1.
	long int			tm_start;		// Time in ms which will be used to know how long it is since the start of the program.
	long int			tot_meals;		// Each time all philos have eaten once, this variable will be incremented.
	t_philo				*philos;		// Pointer to the philos structs.
	pthread_t			*philo_th;		// Pointer to the philos threads.
	pthread_mutex_t		*mutex_fork;	// Mutex that is locked everytime a philo take one fork.
	pthread_mutex_t		*mutex_print;	// Mutex that is locked before anything is printed into the terminal by a thread.
	pthread_mutex_t		*mutex_dead;	// Mutex that is locked everytime before the "one_dead" variable is read or modified.
	pthread_mutex_t		*mutex_meal;	// Mutex that is locked everytme before the "tot_meals" variable is read or modified.
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
long int	time_from_start(t_data *data);
void		sleep_opti(long int sleep_time);

/* UTILS */
int			ft_atoi(const char *str);

/* FREE */
int			_exit_philo(t_data *data);

/* INIT */
int			data_init(t_data *data, char **ac);
int			get_mutex_ready(t_data *data);
int			create_philo_threads(t_data *data);

#endif