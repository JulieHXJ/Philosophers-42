/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junjun <junjun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:28:50 by junjun            #+#    #+#             */
/*   Updated: 2025/03/08 23:59:14 by junjun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	if_starving(t_table *table)
{
	int i;

	i = 0;
	while (i < table->philo_count)
	{
		pthread_mutex_lock(&table->philos_arr[i].meal_lock);
		if (get_current_time() - table->philos_arr[i].last_eat_time > table->time_to_die)
		{
			table->philos_arr[i].dead = true;
			pthread_mutex_unlock(&table->philos_arr[i].meal_lock);
			print_msg("died", &table->philos_arr[i]);
			return(true);
		}
		pthread_mutex_unlock(&table->philos_arr[i].meal_lock);
		i++;
	}
	return (false);
}

static bool if_all_full(t_table *table)
{
	int i;

	i = 0;
	if (table->meals_must_eat == -1)
		return (false);
		
	while (i < table->philo_count)
	{
		pthread_mutex_lock(&table->philos_arr[i].meal_lock);
		if (table->philos_arr[i].count_meal < table->meals_must_eat)
		{
			pthread_mutex_unlock(&table->philos_arr[i].meal_lock);
			return(false);
		}
		pthread_mutex_unlock(&table->philos_arr[i].meal_lock);
		i++;
	}
	return (true);
}

/**
 * ckeck if any philo died and if all full, running parallel to all philos
 */
void *monitor(void *data)
{
	t_table *table;
	int i;

	table =  (t_table *)data;
	while (!table->end_simul)
	{
		if (if_starving(table) || if_all_full(table))
		{
			pthread_mutex_lock(&table->dead_lock);
			table->end_simul = true;
			pthread_mutex_unlock(&table->dead_lock);
			return (NULL);
		}
		ft_usleep(1000);
	}
	return (NULL);
}
