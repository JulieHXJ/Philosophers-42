/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junjun <junjun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 01:32:07 by junjun            #+#    #+#             */
/*   Updated: 2025/02/20 01:54:02 by junjun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool positive_nbr(char *str)
{
	
}

int check_input(char **av)
{
	int i;
	
	i = 1;
	while (av[i])
	{
		if (!positive_nbr(av[i]))
		{
			error_exit("Wrong input: Negative number detacted!");
		}
		if (!ft_isdigit())
		{
			error_exit("Wrong input: Non digit found!");
		}
		if (ft_atol() > INT_MAX)
		{
			error_exit("Wrong input: Value too big!");
		}
		i++;
	}
	return(0);
	
}

void init_table(t_table *table, char **av)
{
	if (check_input() != 0)
	{
		
	}
	table->philo_count = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]) * 1e3;
	table->time_to_eat = ft_atol(av[3]) * 1e3;
	table->time_to_sleep = ft_atol(av[4]) * 1e3;
	//timestamps should > 60ms
	if (table->time_to_die < 6e4 || table->time_to_eat < 6e4 || table->time_to_sleep < 6e4)
	{
		error_exit("Wrong input: timestamp less than 60ms!");
	}
	if (av[5])
	{
		table->meals_must_eat = ft_atol(av[5]);
	}
	else
		table->meals_must_eat = -1;
	table->end_simul = false;
	table->forks_arr = malloc()
}