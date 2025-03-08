/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junjun <junjun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 19:31:55 by junjun            #+#    #+#             */
/*   Updated: 2025/03/08 17:37:37 by junjun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atol(const char *str)
{
	int		i;
	long	res;
	int		sign;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] <= 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - 48;
		i++;
	}
	return (res * sign);
}

int ft_str_isdigit(const char *str)
{
	int i;

	i = 0;
	if (!str || !str[0]) // Handle NULL or empty string
		return (0);
	while (str[i])
	{
		if (str[i] > '9' || str[i] < '0')
		{
			return (1);
		}
		i++;
	}
	return (0);
	
}

int	ft_usleep(long ms)
{
	long	start;
	
	start = get_current_time();
	while ((get_current_time() - start) < ms)
		usleep(500);
	return (0);
}

long	get_current_time(void)
{
	struct timeval	time;
	
	if (gettimeofday(&time, NULL) == -1)
		error_exit("Gettimeofday() error");
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void print_msg(const char *str, t_philo *philo)
{
	long	time;

	pthread_mutex_lock(&philo->table->print_lock);
	time = get_current_time() - philo->table->start_time;
	if (!dead_loop(philo))//todo
		printf(YELLOW"%zu %d %s\n"DEFAULT, time, philo->philo_id, str);
	pthread_mutex_unlock(&philo->table->print_lock);
}
