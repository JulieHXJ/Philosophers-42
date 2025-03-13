/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 01:01:11 by junjun            #+#    #+#             */
/*   Updated: 2025/03/09 15:22:10 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error_exit(const char *msg)
{
	printf(RED "%s\n" DEFAULT, msg);
	exit(EXIT_FAILURE);
}

// Use pthread_mutex_destroy() for each fork and shared mutexes.
// Free allocated memory for forks_arr and philos_arr.
void	clean_table(t_table *table)
{
	int	i;

	pthread_mutex_destroy(&table->print_lock);
	pthread_mutex_destroy(&table->dead_lock);
	if (table->philos_arr)
	{
		i = 0;
		while (i < table->philo_count)
		{
			pthread_mutex_destroy(&table->philos_arr[i].meal_lock);
			i++;
		}
		free(table->philos_arr);
	}
	if (table->forks_arr)
	{
		i = 0;
		while (i < table->philo_count)
		{
			pthread_mutex_destroy(&table->forks_arr[i]);
			i++;
		}
		free(table->forks_arr);
	}
}
