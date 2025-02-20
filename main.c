/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junjun <junjun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 00:20:39 by junjun            #+#    #+#             */
/*   Updated: 2025/02/20 01:52:47 by junjun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"



/**
 * command format: 
 * ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat](optional)
 *  
 */ 

int main(int ac, char **av)
{
	t_table table;
	if (ac != 5 && ac != 6)
	{
		error_exit("Usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat](optional)");
	}
	init_table(&table, av);
	
	if (parsing())
	{
		//clean
	}
	gut_appetit();
	clean_table();//all philo full or one dead
	return(0);
	
}