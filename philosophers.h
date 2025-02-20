/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junjun <junjun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 00:20:24 by junjun            #+#    #+#             */
/*   Updated: 2025/02/20 01:53:08 by junjun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //usleep
#include <stdbool.h>
#include <pthread.h>//mutex, threads
#include <sys/time.h>//gettimeofday
#include <limits.h>

// colors
#define DEFAULT "\033[0m"
#define RED "\033[1;31m"
#define YELLOW "\033[1;33m"
#define WHITE "\033[1;37m"



// structures
typedef pthread_mutex_t t_mtx;

typedef struct s_table t_table;

typedef struct s_forks
{
	t_mtx	fork;
	int	fork_id;
	
} t_forks;

typedef struct s_philo
{
	int id;
	long	count_meal;
	bool	full;
	long	last_eat_time;//count time from last meal
	t_forks *left;
	t_forks *right;
	pthread_t	thread_id;//????
	t_table	*table;
} t_philo;

typedef struct s_table
{
	long philo_count;
	long	time_to_die;
	long 	time_to_eat;
	long 	time_to_sleep;
	long	meals_must_eat;//[5] or -1 if not defined
	long	start_simul;
	bool	end_simul;//if one philo dies or all full
	t_forks *forks_arr;
	t_philo	*philos_arr;
	
} t_table;

// functions

void error_exit(const char *msg);
void init_table(t_table *table, char **av)
#endif