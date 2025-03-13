/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:28:50 by junjun            #+#    #+#             */
/*   Updated: 2025/03/13 17:55:32 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	if_starving(t_table *table)
{
	int		i;
	long	time_since_last_meal;

	i = 0;
	while (i < table->philo_count)
	{
		pthread_mutex_lock(&table->philos_arr[i].meal_lock);
		time_since_last_meal = get_current_time()
			- table->philos_arr[i].last_eat_time;
		if (time_since_last_meal >= table->time_to_die)
		{
			pthread_mutex_lock(&table->dead_lock);
			table->end_simul = true;
			printf(YELLOW "%zu %d died\n" DEFAULT, get_current_time()
				- table->start_time, table->philos_arr[i].philo_id);
			pthread_mutex_unlock(&table->dead_lock);
			pthread_mutex_unlock(&table->philos_arr[i].meal_lock);
			return (true);
		}
		pthread_mutex_unlock(&table->philos_arr[i].meal_lock);
		i++;
	}
	return (false);
}

static bool	if_all_full(t_table *table)
{
	int	i;
	int	finished_eating;

	i = 0;
	finished_eating = 0;
	if (table->meals_must_eat == -1)
		return (false);
	while (i < table->philo_count)
	{
		pthread_mutex_lock(&table->philos_arr[i].meal_lock);
		if (table->philos_arr[i].count_meal >= table->meals_must_eat)
			finished_eating++;
		pthread_mutex_unlock(&table->philos_arr[i].meal_lock);
		i++;
	}
	if (finished_eating == table->philo_count)
	{
		pthread_mutex_lock(&table->dead_lock);
		table->end_simul = true;
		pthread_mutex_unlock(&table->dead_lock);
		return (true);
	}
	return (false);
}

/**
 * ckeck if any philo died and if all full, running parallel to all philos
 */
void	*monitor(void *data)
{
	t_table	*table;

	table = (t_table *)data;
	while (1)
	{
		pthread_mutex_lock(&table->dead_lock);
		if (table->end_simul)
		{
			pthread_mutex_unlock(&table->dead_lock);
			break ;
		}
		pthread_mutex_unlock(&table->dead_lock);
		if (if_starving(table))
			break ;
		if (if_all_full(table))
			break ;
	}
	printf("Monitor thread exiting\n");
	return (NULL);
}

bool	if_end(t_philo *philo)
{
	bool	finish;

	pthread_mutex_lock(&philo->table->dead_lock);
	finish = philo->table->end_simul;
	pthread_mutex_unlock(&philo->table->dead_lock);
	return (finish);
}
