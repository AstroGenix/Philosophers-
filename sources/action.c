/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberehov <dberehov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 16:54:09 by dberehov          #+#    #+#             */
/*   Updated: 2024/04/06 17:19:41 by dberehov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

/**
 * Handles a philosopher's sleep action.
 * • The philosopher sleeps for a set time if simulation hasn't ended.
 * 
 * @param me The philosopher struct.
 * @return true if the simulation has ended, false if the philo is still alive.
 */
bool	nap(t_philo *me)
{
	if (monitor(me, "is sleeping"))
		return (true);
	usleep(me->table->time_to_sleep * 1000);
	return (false);
}

/**
 * Handles a philosopher's action of grabbing forks.
 * • The philosopher attempts to acquire a lock on both left and right forks.
 * • If the simulation has ended during this action, the philosopher drops
 *   the forks and the function returns true.
 *  
 * @param me The philosopher struct.
 * @return true  if the simulation has ended, 
 * 		   false if the philosopher successfully grabbed the forks.
 */
static bool	grab_fork(t_philo *me)
{
	t_table	*val;

	val = me->table;
	pthread_mutex_lock(&(val->fork[me->l_fork]));
	if (monitor(me, "has taken a fork"))
		return (pthread_mutex_unlock(&(val->fork[me->l_fork])), true);
	pthread_mutex_lock(&(val->fork[me->r_fork]));
	if (monitor(me, "has taken a fork"))
		return (pthread_mutex_unlock(&(val->fork[me->r_fork])),
			pthread_mutex_unlock(&(val->fork[me->l_fork])), true);
	return (false);
}

/**
 * Handles a philosopher's action of eating.
 * • The philosopher first attempts to grab both forks.
 * • If successful, the philosopher eats for a specified time,
 *   then drops the forks.
 * • If the simulation has ended during this action,
 * 	 the philosopher drops the forks and the function returns true.
 * 
 * @param me The philosopher struct.
 * @return true if the simulation ended, 
 *         false if the philosopher successfully ate.
 */
bool	eat(t_philo *me)
{
	t_table	*val;

	val = me->table;
	usleep(500);
	if (grab_fork(me))
		return (false);
	pthread_mutex_lock(&(me->table->guilty_spark));
	me->meal_count++;
	me->last_meal_time = get_current_time();
	pthread_mutex_unlock(&(me->table->guilty_spark));
	monitor(me, "is eating");
	usleep(val->time_to_eat * 1000);
	pthread_mutex_unlock(&(val->fork[me->r_fork]));
	pthread_mutex_unlock(&(val->fork[me->l_fork]));
	return (false);
}
