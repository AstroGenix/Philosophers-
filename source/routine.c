/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberehov <dberehov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:55:02 by dberehov          #+#    #+#             */
/*   Updated: 2024/03/24 01:50:55 by dberehov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void nap(t_philo *me)
{
	monitor(me, "is sleeping.");
	usleep(me->table->time_to_sleep * 1000);
}

static int grab_fork(t_philo *me)
{
	if (me->id % 2 == 0)
		pthread_mutex_lock(me->l_fork);
	else
		pthread_mutex_lock(me->r_fork);
	if (!(me->table->sim_end))
		monitor(me, "has taken a fork");
	if (me->id % 2 == 0)
	{
		if (pthread_mutex_lock(me->r_fork) != 0)
			return (pthread_mutex_unlock(me->l_fork), 1);
		if (!(me->table->sim_end))
			monitor(me, "has taken a fork");
	}
	else
	{
		if (pthread_mutex_lock(me->l_fork) != 0)
			return (pthread_mutex_unlock(me->r_fork), 1);
		if (!(me->table->sim_end))
			monitor(me, "has taken a fork");
	}
	return(0);
}

static void eat(t_philo *me)
{
	
	grab_fork(me);
	monitor(me, "is eating");
	pthread_mutex_lock(&me->table->guilty_spark);
	me->last_meal_time = cur_time();
	(me->meal_count)++;
	pthread_mutex_unlock(&me->table->guilty_spark);
	usleep(me->table->time_to_eat * 1000);
	pthread_mutex_unlock(me->r_fork);
	monitor(me, "has dropped a fork");
	pthread_mutex_unlock(me->l_fork);
	monitor(me, "has dropped a fork");
}

void	*routine(void *philo)
{
	t_philo *me;
	
	me = (t_philo *)philo;
	if (me->table->philo_num == 1)
	{
		monitor(me, "has taken a fork");
		return (NULL);
	}
	while (!(me->table->sim_end))
	{
		eat(me);
		nap(me);
		monitor(me, "is thinking");
	}
	return (NULL);
}
