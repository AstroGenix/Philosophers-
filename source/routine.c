/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberehov <dberehov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:55:02 by dberehov          #+#    #+#             */
/*   Updated: 2024/04/02 10:04:19 by dberehov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static long long time_diff(long long past, long long pres)
{
	return(pres - past);
}

static void nap(long long time, t_table *val)
{
	long long i;

	i = cur_time();
	while (val->sim_end == false)
	{
		if (time_diff(i, cur_time()) >= time)
			break ;
		usleep(50);
	}
}

static void eat(t_philo *me)
{
	t_table	*val;

	val = me->table;
	pthread_mutex_lock(&(val->fork[me->l_fork]));
	monitor(me, "has taken a fork");
	pthread_mutex_lock(&(val->fork[me->r_fork]));
	monitor(me, "has taken a fork");
	pthread_mutex_lock(&me->table->guilty_spark);
	monitor(me, "is eating");
	me->last_meal_time = cur_time();
	pthread_mutex_unlock(&me->table->guilty_spark);
	nap(val->time_to_eat, val);
	(me->meal_count)++;
	pthread_mutex_unlock(&(val->fork[me->l_fork]));
	monitor(me, "has dropped a fork");
	pthread_mutex_unlock(&(val->fork[me->r_fork]));
	monitor(me, "has dropped a fork");
}

void	*routine(void *philo)
{
	t_philo *me;
	t_table	*val;
	
	me = (t_philo *)philo;
	val = me->table;
	if (me->table->philo_num == 1)
	{
		monitor(me, "has taken a fork");
		return (NULL);
	}
	if (me->id % 2)
		usleep(10000);
	while (val->sim_end == false)
	{
		eat(me);
		monitor(me, "is sleeping.");
		nap(val->time_to_sleep, val);
		if (val->sim_end == true)
			break ;
		monitor(me, "is thinking");
	}
	return (NULL);
}
