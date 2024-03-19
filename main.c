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
/*
int main()
{
	Check the number of arguments
		exit for wrong num of args 

}
*/
int	main(int argn, char *args[])
{
	t_args 			table;
	t_philo			*philo;
	pthread_mutex_t	*fork;

	if (argn != 5 && argn != 6)
		err_exit("Incorrect number of arguments");
	if (arg_check(argn, args) == true)
		err_exit("One or more arguments are not numbers");
	if (init_values(&table, args) == true)
		err_exit("One or more arguments have invalid values");
	/*fork = initialize_fork(args);*/
	if (philo_start(argn, args) != 0)
		err_exit("Error in philo");
	return (0);
}

int	philo_start(int argn, char **args)
{
	return (0);
}
