/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 00:20:39 by junjun            #+#    #+#             */
/*   Updated: 2025/03/09 17:04:37 by xhuang           ###   ########.fr       */
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
		if (ft_atol(av[i]) == 0 && i != 5)  // Allow 0 only for the 5th argument (meals_must_eat)
    		error_exit("Wrong input: Zero is not allowed for this parameter!");
		if (ft_atol(av[i]) > INT_MAX)
			error_exit("Wrong input: Value too big!");
		i++;
	}
	return (0);
}

/**
 * command format:

	* ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat](optional)
 *
 */
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
