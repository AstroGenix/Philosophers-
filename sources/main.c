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
 * Cleans up resources at the end of the simulation.
 * 
 * @param val The table struct.
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
 * Joins all philosopher threads.
 * 
 * @param val The table struct.
 * @param philo Array of philosopher structs.
 * @return true if thread joining fails, false otherwise.
 */
bool	join_threads(t_table *val, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < val->total_philo)
	{
		if (pthread_join(philo[i].thread_id, NULL) != 0)
		{
			err_exit("Could not join philo thread");
			return (true);
		}
		i++;
	}
	if (val->all_have_eaten == true)
		printf("All philosophers have eaten at least %i meals\n", val->max_meals);
	return (false);
}

/**
 * Creates and starts threads for each philosopher.
 * Initializes the simulation start time and the philosopher's last meal time.
 * Handles the end of the simulation and waits for all threads to finish.
 * 
 * 	i = 0;
	while (i < val->total_philo)
	{
		printf("philo[%d].meal_count = %d\n", i, philo[i].meal_count);
		i++;
	}
 * @param val The table struct.
 * @return true if thread creation or joining fails, false otherwise.
 */
bool	create_threads(t_table *val)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = val->philo;
	val->sim_start_time = get_current_time();
	while (i < val->total_philo)
	{
		philo[i].last_meal_time = get_current_time();
		if (pthread_create(&philo[i].thread_id, NULL,
				routine, (void *)&philo[i]) != 0)
			return (err_exit("Could not create philo thread"), true);
		i++;
	}
	catch_end_clause(val, val->philo);
	if (join_threads(val, philo) == true)
		return (true);
	i = 0;
	while (i < val->total_philo)
	{
		printf("philo[%d].meal_count = %d\n", i, philo[i].meal_count);
		i++;
	}
	return (false);
}
