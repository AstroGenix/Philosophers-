/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberehov <dberehov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:55:02 by dberehov          #+#    #+#             */
/*   Updated: 2024/04/06 17:32:21 by dberehov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

/**
 * Represents the routine of a philosopher during the simulation.
 * • Receives a philosopher struct as a parameter.
 * • If only one philosopher, reports philosopher has taken a fork and ends.
 * • If multiple philosophers, enters a loop where the philosopher:
 *   - Eats, if possible.
 *   - Sleeps, if possible.
 *   - Thinks, if possible.
 * • If philosopher's ID is odd and time to eat >= time to sleep,
 *   waits before starting routine to prevent deadlock.
 * • Loop continues until philosopher can no longer perform actions.
 * 
 * @param philo The philosopher struct.
 * @return NULL when the philosopher's routine is finished.
 */
void	*routine(void *philo)
{
	t_philo	*me;
	t_table	*val;

	me = (t_philo *)philo;
	val = me->table;
	if (me->table->total_philo == 1)
		return (monitor(me, "has taken a fork"), NULL);
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

/**
 * Creates threads for each philosopher.
 * • Iterates through philosophers, initializing last meal time.
 * • Creates threads for each philosopher.
 * • Waits for simulation to end, then joins all threads.
 * 
 * @param val The table struct.
 * @return true if error during thread creation/joining, false otherwise.
 */
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
	return (false);
}

/**
 * Joins all philosopher threads at the end of the simulation.
 * • Iterates through all philosophers and joins their threads.
 * • Outputs message if all the philosophers have eaten max_meals.
 * 
 * @param val The table struct.
 * @param philo The array of philosopher structs.
 * @return true if an error occurred during joining, false otherwise.
 */
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
		printf("All philosophers have eaten %i meals\n", val->max_meals);
	return (false);
}
