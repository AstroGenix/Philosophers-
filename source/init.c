/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberehov <dberehov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 08:14:43 by dberehov          #+#    #+#             */
/*   Updated: 2024/03/20 13:14:14 by dberehov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

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
	if (pthread_mutex_init(&val->guilty_spark, NULL) != 0)
		err_exit("Could not initiate mutex");
	val->sim_end = false;
	return (false);
}

pthread_mutex_t	*init_forks(t_table *val)
{
	pthread_mutex_t	*fork;
	int				i;

	fork = malloc(sizeof(pthread_mutex_t) * val->philo_num);
	if (!fork)
		err_exit("Could not allocate memory for forks");
	i = 0;
	while (i < val->philo_num)
	{
		if (pthread_mutex_init(&fork[i], NULL) != 0)
		{
			while (i-- > 0)
				pthread_mutex_destroy(&fork[i]);
			free(fork);
			err_exit("Could not initialize fork");
		}
		i++;
	}
	return (fork);
}

t_philo	*init_philo(t_table *val, pthread_mutex_t *fork)
{
	t_philo	*philo;
	int		i;

	philo = malloc(sizeof(t_philo) * val->philo_num);
	if (!philo)
		err_exit("Could not allocate memory for philo");
	i = 0;
	while (i < val->philo_num)
	{
		philo[i].id = i + 1;
		philo[i].meal_count = 0;
		philo[i].full = false;
		philo[i].last_meal_time = 0;
		philo[i].l_fork = &fork[i];
		philo[i].r_fork = &fork[(i + 1) % val->philo_num];
		i++;
	}
	return (philo);
}
