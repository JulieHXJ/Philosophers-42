/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:28:50 by junjun            #+#    #+#             */
/*   Updated: 2025/03/10 18:07:07 by xhuang           ###   ########.fr       */
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
			pthread_mutex_unlock(&table->dead_lock);
			print_msg("died", &table->philos_arr[i]);
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
	// printf("Checking if all philosophers ate all meals\n");
	while (i < table->philo_count)
	{
		pthread_mutex_lock(&table->philos_arr[i].meal_lock);
		// printf("Philo %d has eaten %ld meals (needed: %ld)\n", i+1,
			table->philos_arr[i].count_meal, table->meals_must_eat);
		if (table->philos_arr[i].count_meal >= table->meals_must_eat)
			finished_eating++;
		pthread_mutex_unlock(&table->philos_arr[i].meal_lock);
		i++;
	}
	// printf("Total philosophers who finished eating: %d/%ld\n",
		finished_eating, table->philo_count);
	if (finished_eating == table->philo_count)
	{
		// printf("*** ALL PHILOSOPHERS HAVE FINISHED EATING ***\n");
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
	printf("Monitor thread started\n");
	while (1)
	{
		pthread_mutex_lock(&table->dead_lock);
		if (table->end_simul)
		{
			// printf("Monitor detected end_simul = true\n");
			pthread_mutex_unlock(&table->dead_lock);
			break ;
		}
		pthread_mutex_unlock(&table->dead_lock);
		if (if_starving(table))
		{
			// printf("Monitor detected starvation\n");
			break ;
		}
		if (if_all_full(table))
		{
			// printf("Monitor detected all philosophers are full\n");
			break ;
		}
		// if (table->time_to_die > 1)
		// 	usleep(500);
	}
	// printf("Monitor thread exiting\n");
	return (NULL);
}

bool	if_end(t_philo *philo)
{
	bool	finish;

	pthread_mutex_lock(&philo->table->dead_lock);
	finish = philo->table->end_simul;
	pthread_mutex_unlock(&philo->table->dead_lock);
	// if (finish)
	// 	printf("Philo %d detected end condition\n", philo->philo_id);
	return (finish);
}
