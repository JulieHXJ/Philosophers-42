/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 01:32:07 by junjun            #+#    #+#             */
/*   Updated: 2025/03/09 17:14:04 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_forks(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_count)
	{
		if (pthread_mutex_init(&table->forks_arr[i], NULL) != 0)
			error_exit("Forks array mutex init failed");
		i++;
	}
	return (0);
}

static int	init_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_count)
	{
		table->philos_arr[i].table = table;
		table->philos_arr[i].philo_id = i + 1;
		table->philos_arr[i].count_meal = 0;
		table->philos_arr[i].full = false;
		table->philos_arr[i].dead = false;
		table->philos_arr[i].last_eat_time = table->start_time;
		table->philos_arr[i].left_fork = &table->forks_arr[i];
		table->philos_arr[i].right_fork = &table->forks_arr[(i + 1)
			% table->philo_count];
		if (pthread_mutex_init(&table->philos_arr[i].meal_lock, NULL) != 0)
			error_exit("Meal lock init failed");
		i++;
	}
	return (0);
}

int	init_table(t_table *table, char **av)
{
	table->philo_count = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]);
	table->time_to_eat = ft_atol(av[3]);
	table->time_to_sleep = ft_atol(av[4]);
	if (av[5])
		table->meals_must_eat = ft_atol(av[5]);
	else
		table->meals_must_eat = -1;
	table->end_simul = false;
	table->start_time = get_current_time();
	table->philos_arr = malloc(sizeof(t_philo) * table->philo_count);
	table->forks_arr = malloc(sizeof(pthread_mutex_t) * table->philo_count);
	if (!table->philos_arr || !table->forks_arr)
		error_exit("Allocation failed");
	if (pthread_mutex_init(&table->print_lock, NULL) != 0
		|| pthread_mutex_init(&table->dead_lock, NULL) != 0)
		error_exit("Table lock init failed");
	if (init_forks(table) != 0 || init_philos(table) != 0)
		error_exit("Table init failed");
	return (0);
}
