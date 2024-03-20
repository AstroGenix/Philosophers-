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
	t_philo			*philo;
	pthread_mutex_t	*fork;

	if (argn != 5 && argn != 6)
		err_exit("Incorrect number of arguments");
	if (arg_check(argn, args) == true)
		err_exit("One or more arguments are not numbers");
	if (init_values(&table, args) == true)
		err_exit("One or more arguments have invalid values");
	fork = init_fork(&table);
	philo = init_philo(&table, fork);
	create_join_threads(&table, fork, philo);
	return (0);
}

//Outputs the text message
void	log_occur(int i, char *msg, long int time)
{
	const char *color[7] = {"\e[1;91m", "\e[1;92m", "\e[1;93m", "\e[1;94m",
							"\e[1;95m", "\e[1;96m", "\e[1;97m"};
	printf("\e[1;97m%ld \e[0m\t", time);
	if (i > 6)
		if (i % 7 == 0)
			printf("%s%i ",color[0], i);
		else if (i % 5 == 0)
			printf("%s%i ",color[1], i);
		else if (i % 3 == 0)
			printf("%s%i ",color[2], i);
		else if (i % 2 == 0)
			printf("%s%i ",color[3], i);
		else
			printf("%s%i ",color[4], i);
	else
		printf("%s%i ",color[i], i);
	printf("\e[1;97m%s\e[0m\n", msg);
}

void	monitor(t_philo *philo, char *msg)
{
	suseconds_t	time;

	pthread_mutex_lock(&philo->table->guilty_spark);
	if (philo->table->sim_end)
	{
		pthread_mutex_unlock(&philo->table->guilty_spark);
		return ;
	}
	time = cur_time() - philo->start_time;
	log_occur(philo->id, msg, time);
	pthread_mutex_unlock(&philo->table->guilty_spark);
}

void	catch_end_clause(t_table *val, t_philo *philo)
{

}

//Create then join the threads
void	create_join_threads(t_table *val, pthread_mutex_t *fork, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < val->philo_num)
	{
		philo[i].start_time = cur_time();
		if (pthread_create(&philo[i].thread_id, NULL, routine, (void *)&philo[i]) != 0)
			err_exit("Could not create philo thread");
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
