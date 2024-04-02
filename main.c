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

int	main(int argn, char *args[])
{
	t_table			table;

	if (argn != 5 && argn != 6)
		err_exit("Incorrect number of arguments");
	if (arg_check(argn, args) == true)
		err_exit("One or more arguments are not numbers");
	if (init_values(&table, args) == true)
		err_exit("One or more arguments have invalid values");
	if (init_fork(&table) == true)
		err_exit("Fork initiation has failed");
	init_philo(&table);
	create_threads(&table);
	cleanup(&table);
	return (0);
}

void	cleanup(t_table *val)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&val->guilty_spark);
	pthread_mutex_destroy(&val->write_lock);
	while (i < val->philo_num)
	{
		pthread_mutex_destroy(&(val->fork[i]));
		i++;
	}
	return ;
}

//Create then join the threads
void	create_threads(t_table *val)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = val->philo;
	val->sim_start_time = cur_time();
	while (i < val->philo_num)
	{
		if (pthread_create(&philo[i].thread_id, NULL, routine, (void *)&philo[i]) != 0)
			err_exit("Could not create philo thread");
		philo[i].last_meal_time = cur_time();
		i++;
	}
	catch_end_clause(val, philo);
	i = 0;
	while (i < val->philo_num)
	{	
		if (pthread_join(philo[i].thread_id, NULL) != 0)
			err_exit("Could not join philo thread");
		i++;
	}
	return ;
}
