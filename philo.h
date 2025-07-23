/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokon <mokon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 12:00:00 by mokon             #+#    #+#             */
/*   Updated: 2025/07/23 12:00:00 by mokon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_table	t_table;

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	int				id;
}	t_fork;

typedef struct s_philo
{
	int				philo_id;
	long			meals_eaten;
	long			last_meal_time;
	bool			full;
	t_fork			*left_fork;
	t_fork			*right_fork;
	pthread_t		thread;
	pthread_mutex_t	philo_mutex;
	t_table			*table;
}	t_philo;

typedef struct s_table
{
	long			philo_nbr;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			meals_limit_count;
	bool			stop_simulation;
	bool			threads_ready;
	long			threads_running_nbr;
	pthread_mutex_t	table_mutex;
	pthread_mutex_t	write_mutex;
	pthread_t		death_monitor;
	long			start_simulation;
	t_philo			*philos;
	t_fork			*forks;
	pthread_mutex_t	print_mutex;
}	t_table;

void			input_parsing(t_table *table, char **argv);
const char		*input_checker(const char *str);
void			data_init(t_table *table);
long			ft_atol(const char *str);
void			error_exit(const char *error);
void			*safe_malloc(size_t bytes);
void			dinner_start(t_table *table);
void			*single_philo(void *arg);
void			*dinner_simulation(void *data);
void			*monitor_dinner(void *data);
void			desynchronize_philos(t_philo *philo);
void			write_status(t_philo *philo, char *status);
void			thinking(t_philo *philo, bool before_dinner);
bool			simulation_finished(t_table *table);
void			wait_all_threads(t_table *table);
long			get_current_time(char *code);
void			ft_usleep(long usec, t_table *table);
void			thread_handle(pthread_t *thread, const char *code,
					void *(*start_routine)(void *), void *arg);
void			mutex_handle(pthread_mutex_t *mtx, const char *code);
int				ft_strcmp(const char *s1, const char *s2);
void			bool_setter(pthread_mutex_t *mtx, bool *dest, bool value);
bool			bool_getter(pthread_mutex_t *mtx, bool *value);
void			long_setter(pthread_mutex_t *mtx, long *dest, long value);
long			long_getter(pthread_mutex_t *mtx, long *value);
void			increase_long(pthread_mutex_t *mtx, long *value);
bool			all_threads_running(pthread_mutex_t *mtx,
					long *threads, long nbr);
void			clean(t_table *table);

#endif
