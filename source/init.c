/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberehov <dberehov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 08:14:43 by dberehov          #+#    #+#             */
/*   Updated: 2024/04/02 11:14:41 by dberehov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

/**
 * Initializes the simulation values based on command-line arguments.
 * • Parses and stores the number of philosophers, time to die, time to eat,
 *   time to sleep, and optionally the maximum meals.
 * • Initializes mutexes for simulation control and writing to standard output.
 *
 * @param val The simulation table to initialize.
 * @param args Command-line arguments provided to the program.
 * @return True if any error occurs during initialization, false otherwise.
 */
bool	init_values(t_table *val, char **args)
{
	val->philo_num = ft_atoi(args[1]);
	val->time_to_die = ft_atoi(args[2]);
	val->time_to_eat = ft_atoi(args[3]);
	val->time_to_sleep = ft_atoi(args[4]);
	val->max_meals = -1;
	if (args[5])
		val->max_meals = ft_atoi(args[5]);
	if (val->philo_num == 0 || val->max_meals == 0)
		return (true);
	if (pthread_mutex_init(&(val->guilty_spark), NULL) != 0)
		err_exit("Could not init 'guilty_spark' mutex");
	if (pthread_mutex_init(&(val->write_lock), NULL) != 0)
		err_exit("Could not init 'write_lock' mutex");
	val->sim_end = false;
	val->sim_start_time = 0;
	return (false);
}

/**
 * Initializes mutexes for each available fork.
 * • Each philosopher has a left and right fork, represented by a mutex.
 * • Forks are shared resources, necessitating mutexes to avoid data races.
 *
 * @param val The simulation table containing the forks.
 */
void	init_fork(t_table *val)
{
	int				i;

	i = 0;
	while (i >= val->philo_num)
	{
		if (pthread_mutex_init(&(val->fork[i]), NULL) != 0)
			err_exit("Could not initialize fork");
		i++;
	}
	return ;
}

/**
 * Initializes philosophers with their IDs and respective forks.
 * • Each philosopher is assigned a unique ID.
 * • Forks are allocated based on the philosopher's ID, ensuring adjacent
 *   philosophers share a fork.
 * • Initializes each philosopher's meal count and last meal time.
 *
 * @param val The simulation table with philosophers to initialize.
 */
void	init_philo(t_table *val)
{
	int		i;

	i = 0;
	while (i < val->philo_num)
	{
		val->philo[i].id = i + 1;
		val->philo[i].meal_count = 0;
		val->philo[i].last_meal_time = 0;
		val->philo[i].l_fork = i;
		val->philo[i].r_fork = (i + 1) % val->philo_num;
		val->philo[i].table = val;
		i++;
	}
	return ;
}
