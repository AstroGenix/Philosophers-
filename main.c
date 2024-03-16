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
	t_table table;

	if (argn != 5 && argn != 6)
		err_exit("Incorrect number of arguments");
	if (arg_check(argn, args) == true)
		err_exit("One or more arguments are not numbers");
	if (init_values(&table, args) == true)
		err_exit("One or more arguments have invalid values");
	if (philo(argn, args) != 0)
		err_exit("Error in philo");
	return (0);
}

//Initiate and check for valid values
bool	init_values(t_table *val, char **args)
{
	val->philo_num = ft_atoi(args[1]);
	val->time_to_die = ft_atoi(args[2]);
	val->time_to_eat = ft_atoi(args[3]);
	val->time_to_sleep = ft_atoi(args[4]);
	if (args[5])
		val->max_meals = ft_atoi(args[5]);
	else
		val->max_meals = -1;
	if (val->philo_num == 0 || val->max_meals == 0)
		return (true);
}

int	philo(int argn, char **args)
{
	return (0);
}
