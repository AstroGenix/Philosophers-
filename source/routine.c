/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberehov <dberehov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:55:02 by dberehov          #+#    #+#             */
/*   Updated: 2024/04/02 12:45:10 by dberehov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

/**
 * Calculates the time difference between two timestamps.
 * • Useful for tracking durations or intervals in the simulation.
 *
 * @param past The earlier timestamp.
 * @param pres The later timestamp.
 * @return The difference between pres and past in milliseconds.
 */
static long long	time_diff(long long past, long long pres)
{
	return (pres - past);
}

/**
 * Pauses execution for a specified amount of time.
 * • Implements a non-blocking wait that periodically checks if the simulation
 *   has ended.
 * • Uses a while loop and usleep to efficiently wait without
 * 	 hogging CPU resources.
 *
 * @param time The duration to nap in milliseconds.
 * @param val The simulation table for checking the simulation's end condition.
 */
static void	nap(long long time, t_table *val)
{
	long long	timestamp;

	timestamp = get_current_time();
	while (val->sim_end == false)
	{
		if (time_diff(timestamp, get_current_time()) >= time)
			break ;
		usleep(50);
	}
}

static void	grab_fork(t_philo *me, t_table *val)
{
	if (me->id % 2)
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

/**
 * Handles the eating routine for a philosopher.
 * • Locks the left and right fork mutexes to simulate taking forks.
 * • Marks the philosopher as eating and updates their last meal time.
 * • Unlocks the fork mutexes after eating.
 *
 * @param me The philosopher struct representing the current philosopher.
 */
static void	eat(t_philo *me)
{
	t_table	*val;

	val = me->table;
	grab_fork(me, val);
	pthread_mutex_lock(&me->table->guilty_spark);
	monitor(me, "is eating");
	me->last_meal_time = get_current_time();
	(me->meal_count)++;
	pthread_mutex_unlock(&me->table->guilty_spark);
	nap(val->time_to_eat, val);
	pthread_mutex_unlock(&(val->fork[me->r_fork]));
	monitor(me, "has dropped a fork");
	pthread_mutex_unlock(&(val->fork[me->l_fork]));
	monitor(me, "has dropped a fork");
}

/**
 * The main routine of each philosopher thread.
 * • Philosopher with odd IDs start by taking a short nap to reduce contention.
 * • Enters a loop of eating, sleeping, and thinking until the simulation ends.
 *
 * @param philo The philosopher struct representing the current philosopher.
 * @return NULL
 */
void	*routine(void *philo)
{
	t_philo	*me;
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
