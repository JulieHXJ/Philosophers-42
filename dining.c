/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:49:44 by junjun            #+#    #+#             */
/*   Updated: 2025/03/10 18:06:38 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	thinking(t_philo *philo)
{
	long	time_to_think;

	if (if_end(philo))
		return ;
	pthread_mutex_lock(&philo->meal_lock);
	time_to_think = (philo->table->time_to_die - (get_current_time()
				- philo->last_eat_time) - philo->table->time_to_eat) / 2;
	pthread_mutex_unlock(&philo->meal_lock);
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think == 0)
		time_to_think = 1;
	if (time_to_think > 600)
		time_to_think = 200;
	print_msg("is thinking", philo);
	philo->full = false;
	// Add a small random thinking time to break synchronization
	ft_usleep(time_to_think, philo);
}

static void	sleeping(t_philo *philo)
{
	if (if_end(philo))
		return ;
	print_msg("is sleeping", philo);
	ft_usleep(philo->table->time_to_sleep, philo);
}

static bool	take_fork(t_philo *philo, pthread_mutex_t *fork)
{
	pthread_mutex_lock(fork);
	if (if_end(philo))
	{
		pthread_mutex_unlock(fork);
		return (false);
	}
	print_msg("has taken a fork", philo);
	return (true);
}

/**
 * all philo pick right fork firstlt, but the last pick left fork
 */
static void	eating(t_philo *philo)
{
	if (if_end(philo))
		return ;
	if (philo->philo_id % 2 == 0)
	{
		if (!take_fork(philo, philo->left_fork))
			return ;
		if (!take_fork(philo, philo->right_fork))
		{
			pthread_mutex_unlock(philo->right_fork);
			return ;
		}
	}
	else
	{
		if (!take_fork(philo, philo->right_fork))
			return ;
		ft_usleep(1, philo);
		if (!take_fork(philo, philo->left_fork))
		{
			pthread_mutex_unlock(philo->left_fork);
			return ;
		}
	}
	print_msg("is eating", philo);
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_eat_time = get_current_time();
	philo->count_meal++;
	pthread_mutex_unlock(&philo->meal_lock);
	ft_usleep(philo->table->time_to_eat, philo);
	philo->full = true;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	*dining_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->table->philo_count == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_msg("has taken a fork", philo);
		ft_usleep(philo->table->time_to_die, philo);
		pthread_mutex_lock(&philo->table->dead_lock);
		philo->dead = true;
		philo->table->end_simul = true;
		pthread_mutex_unlock(&philo->table->dead_lock);
		print_msg("died", philo);
		pthread_mutex_unlock(philo->left_fork);
		printf("single philo finished\n");
		// printf("single in routine finished\n");
		return (NULL);
	}
	if (philo->philo_id % 2 == 0)
		ft_usleep(philo->table->time_to_eat / 2, philo);
	while (!if_end(philo))
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (data);
}
