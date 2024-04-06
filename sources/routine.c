/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberehov <dberehov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:55:02 by dberehov          #+#    #+#             */
/*   Updated: 2024/04/05 17:57:13 by dberehov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*routine(void *philo)
{
	t_philo	*me;
	t_table	*val;

	me = (t_philo *)philo;
	val = me->table;
	if (me->table->total_philo == 1)
		return (monitor(me, "has taken a fork"),NULL);
	while (true)
	{
		if (me->id % 2 == 1 && val->time_to_eat - val->time_to_sleep >= 0)
			usleep((1 + val->time_to_eat - val->time_to_sleep) * 1000);
		if (eat(me))
			break ;
		if (nap(me))
			break ;
		if (monitor(me, "is thinking"))
			break ;
	}
	return (NULL);
}

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
