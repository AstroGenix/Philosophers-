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

#include "include/philosophers.h"

/**
 * The main function to initiate the philosopher simulation.
 * • Verifies the correct number and format of arguments.
 * • Initializes the simulation table and philosopher properties.
 * • Starts the philosopher threads and then joins them once finished.
 * • Cleans up resources after the simulation ends.
 */
int	main(int argn, char *args[])
{
	t_table			table;

	if (argn != 5 && argn != 6)
		err_exit("Incorrect number of arguments");
	if (arg_check(argn, args) == true)
		err_exit("One or more arguments are not numbers");
	if (init_values(&table, args) == true)
		err_exit("One or more arguments have invalid values");
	init_fork(&table);
	init_philo(&table);
	create_threads(&table);
	cleanup(&table);
	return (0);
}

/**
 * Cleans up all initialized mutexes.
 * • Destroys the mutexes.
 * • Iterates over each fork mutex to destroy it,
 * ensuring no resources are leaked.
 *
 * @param val The simulation table containing the mutexes.
 */
void	cleanup(t_table *val)
{
	int	i;

	i = val->total_philo;
	pthread_mutex_destroy(&val->guilty_spark);
	pthread_mutex_destroy(&val->write_lock);
	while (i < val->total_philo)
	{
		pthread_mutex_destroy(&(val->fork[i]));
		i--;
	}
	return ;
}

/**
 * Initiates philosopher threads and manages their lifecycle.
 * • Sets simulation start time.
 * • Creates a thread for each philosopher, setting their last meal time.
 *   - Exits with an error if thread creation fails.
 * • Calls catch_end_clause to await the simulation's end condition,
 *   either when all meals are finished or a philosopher dies.
 * • Joins all threads, ensuring completion and resource cleanup.
 * 
 * @param val The simulation table with philosopher and simulation data.
 */
void	create_threads(t_table *val)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = val->philo;
	val->sim_start_time = get_current_time();
	while (i < val->total_philo)
	{
		if (pthread_create(&philo[i].thread_id, NULL, routine,
				(void *)&philo[i]) != 0)
			err_exit("Could not create philo thread");
		philo[i].last_meal_time = get_current_time();
		i++;
	}
	catch_end_clause(val, val->philo);
	
	i = 0;
	while (i < val->total_philo)
	{
		if (pthread_join(philo[i].thread_id, NULL) != 0)
			err_exit("Could not join philo thread");
		i++;
	}
	if (val->all_have_eaten == true);
		printf("All philosophers have finished dining.\n");
	return ;
}
