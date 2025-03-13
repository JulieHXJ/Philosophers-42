/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junjun <junjun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 00:20:39 by junjun            #+#    #+#             */
/*   Updated: 2025/03/13 21:43:39 by junjun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// ensure positive numbers, but number of meals could be zero
int	check_value(char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (ft_str_isdigit(av[i]) != 0)
			error_exit("Wrong input: Non digit found!");
		if (ft_atol(av[i]) < 0)
			error_exit("Wrong input: Negative number detected!");
		if (ft_atol(av[i]) == 0 && i != 5)
			error_exit("Wrong input: Zero is not allowed for this parameter!");
		if (ft_atol(av[i]) > INT_MAX)
			error_exit("Wrong input: Value too big!");
		i++;
	}
	return (0);
}

int	gut_appetit(t_table *table)
{
	pthread_t	checker_thread;
	int			i;

	i = 0;
	if (table->meals_must_eat == 0)
		return (0);
	if (pthread_create(&checker_thread, NULL, &monitor, table) != 0)
		return (clean_table(table), 1);
	while (i < table->philo_count)
	{
		if (pthread_create(&table->philos_arr[i].thread_id, NULL,
				&dining_routine, &table->philos_arr[i]) != 0)
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

int	main(int ac, char **av)
{
	t_table	table;

	if (ac != 5 && ac != 6)
		error_exit(USAGE_MSG);
	if (check_value(av) != 0)
		return (1);
	if (init_table(&table, av) != 0)
		return (clean_table(&table), 1);
	if (gut_appetit(&table))
		return (clean_table(&table), 1);
	clean_table(&table);
	return (0);
}
