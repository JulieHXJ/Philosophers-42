/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junjun <junjun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:49:44 by junjun            #+#    #+#             */
/*   Updated: 2025/03/09 00:27:48 by junjun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void thinking(t_philo *philo)
{
	print_msg("is thinking", philo);
	philo->full = false;
}

static void sleeping(t_philo *philo)
{
	print_msg("is sleeping", philo);
	ft_usleep(philo->table->time_to_sleep);
}

/**
 * all philo pick right fork firstlt, but the last pick left fork
 */
static void eating(t_philo *philo)
{
	if (philo->philo_id == philo->table->philo_count)
	{
		pthread_mutex_lock(&philo->left_fork);
		print_msg("has taken a fork", philo);
		pthread_mutex_lock(&philo->right_fork);
		print_msg("has taken a fork", philo);
	}
	else
	{
		pthread_mutex_lock(&philo->right_fork);
		print_msg("has taken a fork", philo);
		pthread_mutex_lock(&philo->left_fork);
		print_msg("has taken a fork", philo);
	}
	print_msg("is eating", philo);
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_eat_time = get_current_time();
	philo->count_meal++;
	pthread_mutex_unlock(&philo->meal_lock);
	ft_usleep(philo->table->time_to_eat);
	philo->full = true;
	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(&philo->right_fork);
	
}



void *dining_routine(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;
	if (philo->table->philo_count == 1 && !check_dead_philo(philo))
	{
		pthread_mutex_lock(philo->left_fork);
		print_msg("has taken a fork", philo);
		ft_usleep(philo->table->time_to_die);
		pthread_mutex_unlock(philo->left_fork);
		return (NULL);
	}
	if (philo->philo_id % 2 == 0)
		ft_usleep(philo->table->time_to_eat / 2);
	while (!if_end(philo))
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

int gut_appetit(t_table *table)
{
	pthread_t checker_thread;
	int i;

	i = 0;
	if (table->meals_must_eat == 0)
		return (0);
	if (pthread_create(&checker_thread, NULL, &monitor, &table) != 0)//todo
		return (clean_table(table), 1);
	while (i < table->philo_count)
	{
		if (pthread_create(&table->philos_arr[i].thread_id, NULL, &dining_routine, &table->philos_arr[i]) != 0)
			return (clean_table(table), 1);
		i++;
	}
	if (pthread_join(checker_thread, NULL) != 0)
		return (clean_table(table), 1);
	i = 0;
	while (i < table->philo_count)
	{
		if (pthread_join(table->philos_arr[i].thread_id, NULL) != 0)
			return (clean_table(table), 1);
		i++;
	}
	return (0);
}
