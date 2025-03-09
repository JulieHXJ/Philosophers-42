/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:28:50 by junjun            #+#    #+#             */
/*   Updated: 2025/03/09 18:40:31 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	if_starving(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_count)
	{
		pthread_mutex_lock(&table->philos_arr[i].meal_lock);
		if (get_current_time() - table->philos_arr[i].last_eat_time >= table->time_to_die)
		{
			pthread_mutex_lock(&table->dead_lock);
			table->end_simul = true;
			pthread_mutex_unlock(&table->dead_lock);
			pthread_mutex_lock(&table->print_lock);
			print_msg("died", &table->philos_arr[i]);
			pthread_mutex_unlock(&table->print_lock);
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


	// while (i < table->philo_count)
	// {
	// 	pthread_mutex_lock(&table->philos_arr[i].meal_lock);
	// 	if (table->philos_arr[i].count_meal < table->meals_must_eat)
	// 	{
	// 		pthread_mutex_unlock(&table->philos_arr[i].meal_lock);
	// 		return (false);
	// 	}
	// 	pthread_mutex_unlock(&table->philos_arr[i].meal_lock);
	// 	i++;
	// }
	// pthread_mutex_lock(&table->dead_lock);
	// table->end_simul = true;
	// pthread_mutex_unlock(&table->dead_lock);
	// return (true);
	
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
		if (if_starving(table) || if_all_full(table))
		{
            break;
		}
        ft_usleep(500, NULL); // Sleep 0.1ms for small time_to_die
	}
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
