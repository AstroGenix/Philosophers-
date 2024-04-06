/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberehov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 09:31:34 by dberehov          #+#    #+#             */
/*   Updated: 2024/01/17 09:31:35 by dberehov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	main(int argn, char *args[])
{
	t_table			table;

	if (argn != 5 && argn != 6)
		return (1);
	if (arg_check(args) == true)
		return (1);
	if (init_values(&table, args) == true)
		return (1);
	if (init_fork(&table) == true)
		return (1);
	init_philo(&table);
	if (create_threads(&table) == true)
		return (1);
	cleanup(&table);
	return (0);
}

/**
 * Handles the cleanup process at the end of the simulation.
 * • Destroys the mutex for 'guilty_spark'.
 * • Iterates through all philosophers and destroys their fork mutexes.
 * 
 * @param val The table struct.
 */
void	cleanup(t_table *val)
{
	int	i;

	i = val->total_philo;
	pthread_mutex_destroy(&val->guilty_spark);
	while (i < val->total_philo)
	{
		pthread_mutex_destroy(&(val->fork[i]));
		i--;
	}
	return ;
}
