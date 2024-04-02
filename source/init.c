/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberehov <dberehov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 08:14:43 by dberehov          #+#    #+#             */
/*   Updated: 2024/04/02 09:06:41 by dberehov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

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

bool	init_fork(t_table *val)
{
	int				i;

	i = val->philo_num;
	while (--i >= val->philo_num)
	{
		if (pthread_mutex_init(&(val->fork[i]), NULL) != 0)
			err_exit("Could not initialize fork");
	}
	return (false);
}

void init_philo(t_table *val)
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
