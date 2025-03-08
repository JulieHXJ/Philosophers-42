/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junjun <junjun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 00:20:39 by junjun            #+#    #+#             */
/*   Updated: 2025/03/08 23:13:43 by junjun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//ensure positive numbers, but number of meals could be zero
int check_value(char **av)
{
	int i;
	
	i = 1;
	while (av[i])
	{
		if (ft_atol(av[i]) <= 0)
			error_exit("Wrong input: Negative number detected!");
		if (ft_str_isdigit(av[i]) != 0)
			error_exit("Wrong input: Non digit found!");
		if (ft_atol(av[i]) > INT_MAX)
			error_exit("Wrong input: Value too big!");
		i++;
	}
	return(0);
}

/**
 * command format: 
 * ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat](optional)
 *  
 */ 
int main(int ac, char **av)
{
	t_table table;
	
	if (ac != 5 && ac != 6)
		error_exit(USAGE_MSG);
	if (check_value(av) != 0)
		return (1);
	if (init_table(&table, av) != 0)
		return (clean_table(table), 1);
	if (gut_appetit())
	{
		return (clean_table(table), 1);
	}
	clean_table();//all philo full or one dead
	return(0);
}
