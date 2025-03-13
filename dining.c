/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:49:44 by junjun            #+#    #+#             */
/*   Updated: 2025/03/13 17:46:43 by xhuang           ###   ########.fr       */
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
	ft_usleep(time_to_think, philo);
}

static void	sleeping(t_philo *philo)
{
	if (if_end(philo))
		return ;
	print_msg("is sleeping", philo);
	ft_usleep(philo->table->time_to_sleep, philo);
}

static bool	take_forks(t_philo *philo, pthread_mutex_t *first_fork,
		pthread_mutex_t *second_fork)
{
	pthread_mutex_lock(first_fork);
	if (if_end(philo))
		return (pthread_mutex_unlock(first_fork), false);
	print_msg("has taken a fork", philo);
	pthread_mutex_lock(second_fork);
	if (if_end(philo))
	{
		pthread_mutex_unlock(first_fork);
		pthread_mutex_unlock(second_fork);
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
	bool	forks_taken;

	if (if_end(philo))
		return ;
	if (philo->philo_id % 2 == 0)
		forks_taken = take_forks(philo, philo->left_fork, philo->right_fork);
	else
		forks_taken = take_forks(philo, philo->right_fork, philo->left_fork);
	if (!forks_taken)
		return ;
	print_msg("is eating", philo);
	pthread_mutex_lock(&philo->meal_lock);
	philo->count_meal++;
	philo->last_eat_time = get_current_time();
	pthread_mutex_unlock(&philo->meal_lock);
	ft_usleep(philo->table->time_to_eat, philo);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	*dining_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (if_end(philo))
		return (NULL);
	if (philo->table->philo_count == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_msg("has taken a fork", philo);
		ft_usleep(philo->table->time_to_die, philo);
		pthread_mutex_lock(&philo->table->dead_lock);
		philo->table->end_simul = true;
		pthread_mutex_unlock(&philo->table->dead_lock);
		pthread_mutex_unlock(philo->left_fork);
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
	return (NULL);
}
