/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberehov <dberehov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:55:02 by dberehov          #+#    #+#             */
/*   Updated: 2024/04/02 16:40:58 by dberehov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	nap(long long time, t_table *val)
{
	long long	timestamp;

	timestamp = get_current_time();
	while (true)
	{
		if (time_diff(timestamp, get_current_time()) >= time)
			break ;
		usleep(10);
	}
}

static void grab_fork(t_philo *me)
{
	t_table	*val;

	val = me->table;
	if (me->id % 2 == 0)
	{
		pthread_mutex_lock(&(val->fork[me->l_fork]));
		monitor(me, "has taken a fork");
		pthread_mutex_lock(&(val->fork[me->r_fork]));
		monitor(me, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&(val->fork[me->r_fork]));
		monitor(me, "has taken a fork");
		pthread_mutex_lock(&(val->fork[me->l_fork]));
		monitor(me, "has taken a fork");
	}
}
static void	eat(t_philo *me)
{
	t_table	*val;

	val = me->table;
	grab_fork(me);
	pthread_mutex_lock(&(me->table->guilty_spark));
	monitor(me, "is eating");
	(me->meal_count)++;
	me->last_meal_time = get_current_time(); // update last_meal_time after eating
	pthread_mutex_unlock(&(me->table->guilty_spark));
	nap(val->time_to_eat, val);
	if (me->id % 2 == 0)
	{
		pthread_mutex_unlock(&(val->fork[me->r_fork]));
		pthread_mutex_unlock(&(val->fork[me->l_fork]));
	}
	else
	{
		pthread_mutex_unlock(&(val->fork[me->l_fork]));
		pthread_mutex_unlock(&(val->fork[me->r_fork]));
	}
}

static bool	check_end_clause(t_table *val, t_philo *me)
{
	pthread_mutex_lock(&(val->guilty_spark));
	if (val->all_have_eaten == true || val->sim_end == true)
	{
   		pthread_mutex_unlock(&(val->guilty_spark));
		return (true);
	}
	pthread_mutex_unlock(&(val->guilty_spark));
	return (false);
}

void	*routine(void *philo)
{
	t_philo	*me;
	t_table	*val;

	me = (t_philo *)philo;
	val = me->table;
	if (me->table->total_philo == 1)
	{
		monitor(me, "has taken a fork");
		return (NULL);
	}
	if (me->id % 2)
		usleep(10000);
	while (true)
	{
		if (check_end_clause(val, me))
			break ;
		eat(me);
		monitor(me, "is sleeping");
		nap(val->time_to_sleep, val);
		monitor(me, "is thinking");
	}
	return (NULL);
}
