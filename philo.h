/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junjun <junjun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 00:20:24 by junjun            #+#    #+#             */
/*   Updated: 2025/03/13 21:44:05 by junjun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h> //mutex, threads
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h> //gettimeofday
# include <unistd.h>   //usleep

// colors
# define DEFAULT "\033[0m"
# define RED "\033[1;31m"
# define YELLOW "\033[1;33m"
# define WHITE "\033[1;37m"

# define USAGE_MSG \
	"Usage: ./philo number_of_philosophers time_to_die time_to_eat \
time_to_sleep [number_of_times_each_philosopher_must_eat](optional)"

// structures
typedef struct s_table	t_table;

typedef struct s_philo
{
	pthread_t			thread_id;
	int					philo_id;
	long				count_meal;
	long				last_eat_time;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	t_table				*table;
	pthread_mutex_t		meal_lock;
}						t_philo;

typedef struct s_table
{
	long				philo_count;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				meals_must_eat;
	long				start_time;
	bool				end_simul;
	t_philo				*philos_arr;
	pthread_mutex_t		*forks_arr;
	pthread_mutex_t		print_lock;
	pthread_mutex_t		dead_lock;
}						t_table;

// functions
void					error_exit(const char *msg);
int						init_table(t_table *table, char **av);
void					*dining_routine(void *data);
void					*monitor(void *data);
bool					if_end(t_philo *philo);
void					clean_table(t_table *table);

// utils
long					ft_atol(const char *str);
int						ft_str_isdigit(const char *str);
long					get_current_time(void);
int						ft_usleep(long millisecond, t_philo *philo);
void					print_msg(const char *str, t_philo *philo);

#endif