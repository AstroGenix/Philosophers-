/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberehov <dberehov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:55:02 by dberehov          #+#    #+#             */
/*   Updated: 2024/03/20 17:08:38 by dberehov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void nap(t_philo *me)
{
	monitor(me, "is sleeping.");
	usleep(me->table->time_to_sleep * 1000);
}

static void drop_fork(t_philo *me)
{
	if (me->id % 2 == 0)
	{
		pthread_mutex_unlock(me->l_fork);
		monitor(me, "dropped left fork");
		pthread_mutex_unlock(me->r_fork);
		monitor(me, "dropped right fork");
	}
	else
	{
		pthread_mutex_unlock(me->r_fork);
		monitor(me, "dropped right fork");
		pthread_mutex_unlock(me->l_fork);
		monitor(me, "dropped left fork");
	}
}


static void grab_fork(t_philo *me)
{
	if (me->id % 2 == 0)
	{
		pthread_mutex_lock(me->l_fork);
		monitor(me, "grabbed left fork");
		pthread_mutex_lock(me->r_fork);
		monitor(me, "grabbed right fork");
	}
	else
	{
		pthread_mutex_lock(me->r_fork);
		monitor(me, "grabbed right fork");
		pthread_mutex_lock(me->l_fork);
		monitor(me, "grabbed left fork");
	}
}

static void eat(t_philo *me)
{
	grab_fork(me);
	pthread_mutex_lock(&me->table->guilty_spark);
	me->meal_count++;
	me->last_meal_time = cur_time();
	pthread_mutex_unlock(&me->table->guilty_spark);
	monitor(me, "is eating");
	usleep(me->table->time_to_eat * 1000);
	drop_fork(me);
}

void	*routine(void *philo)
{
	t_philo *me;
	
	me = (t_philo *)philo;
	if (me->table->philo_num == 1)
	{
		monitor(me, "grabbed only fork");
		return (NULL);
	}
	while (true)
	{
		pthread_mutex_lock(&me->table->guilty_spark);
		if (me->table->sim_end)
		{
			pthread_mutex_unlock(&me->table->guilty_spark);
			break ;
		}
		pthread_mutex_unlock(&me->table->guilty_spark);
		eat(me);
		nap(me);
		monitor(me, "is thinking");
	}
	return (NULL);
}
