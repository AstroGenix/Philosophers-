/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_sim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberehov <dberehov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 10:22:47 by dberehov          #+#    #+#             */
/*   Updated: 2024/04/02 11:16:01 by dberehov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

/**
 * Marks the simulation as ended and logs a message indicating the philosophers
 * have finished dining.
 * • This function locks the write lock to ensure thread-safe output.
 * • It is called when all philosophers have eaten the required number of
 *   meals.
 *
 * @param val The simulation table containing the simulation state.
 */
static void	end_sim(t_table	*val)
{
	val->sim_end = true;
	pthread_mutex_lock(&val->write_lock);
	printf("Philosophers have finished dining\n");
	pthread_mutex_unlock(&val->write_lock);
	pthread_mutex_unlock(&val->guilty_spark);
}

/**
 * Checks if a philosopher has died from starvation.
 * • It compares the current time with the philosopher's last meal time and
 *   the allowed time to die.
 * • If the philosopher is dead, it marks the simulation as ended.
 *
 * @param val The simulation table containing the simulation state.
 * @param philo The philosopher to check for starvation.
 * @return True if the philosopher is dead, otherwise False.
 */
static bool	is_dead(t_table *val, t_philo *philo)
{
	if (((get_current_time() - philo->last_meal_time)
			>= philo->table->time_to_die))
	{
		monitor(philo, "died");
		val->sim_end = true;
		pthread_mutex_unlock(&val->guilty_spark);
		return (true);
	}
	return (false);
}

/**
 * Monitors the end conditions of the simulation, including starvation and
 * meal completion.
 * • It continuously checks each philosopher for death by starvation and if all
 *   philosophers have eaten the required number of meals.
 * • If any philosopher dies or all philosophers have eaten the required number
 *   of meals, it triggers the end of the simulation.
 *
 * @param val The simulation table containing the simulation state and
 * philosophers.
 * @param philo Array of philosophers participating in the simulation.
 */
void	catch_end_clause(t_table *val, t_philo *philo)
{
	int		i;
	bool	full_count;

	while (true)
	{
		i = -1;
		full_count = true;
		pthread_mutex_lock(&val->guilty_spark);
		while (++i < val->philo_num)
		{
			if (philo[i].meal_count < philo->table->max_meals
				|| val->max_meals < 0)
				full_count = false;
			if (is_dead(val, &philo[i]))
				return ;
		}
		if (full_count)
			return (end_sim(val));
		pthread_mutex_unlock(&val->guilty_spark);
	}
}
