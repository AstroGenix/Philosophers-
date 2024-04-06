/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_sim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberehov <dberehov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 10:22:47 by dberehov          #+#    #+#             */
/*   Updated: 2024/04/05 22:17:57 by dberehov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

/**
 * Calculates the time difference between two timestamps.
 * 
 * @param past The past timestamp.
 * @param pres The present timestamp.
 * @return The difference between the two timestamps.
 */
long long	time_diff(long long past, long long pres)
{
	return (pres - past);
}

/**
 * Checks if all philosophers have eaten the maximum number of meals.
 * If so, it sets the simulation to end.
 * 
 * @param val The table struct.
 * @param philo Array of philosopher structs.
 */
static bool	check_all_philos_eaten(t_table *val, t_philo *philo)
{
	int	i;

	i = 0;
	while (val->max_meals != -1 && i < val->total_philo
		&& philo[i].meal_count >= val->max_meals)
		i++;
	if (i == val->total_philo)
	{
		val->all_have_eaten = true;
		return (true);
	}
	return (false);
}

/**
 * Checks if the simulation should end.
 * If a philosopher has died or all philosophers have eaten the maximum number
 * of meals, it sets the simulation to end.
 * 
 * @param val The table struct.
 * @param philo Array of philosopher structs.
 */
void	catch_end_clause(t_table *val, t_philo *philo)
{
	int	i;

	while (true)
	{
		i = 0;
		pthread_mutex_lock(&(val->guilty_spark));
		while (i < val->total_philo)
		{
			if (time_diff(philo[i].last_meal_time,get_current_time()) > val->time_to_die)
			{
				pthread_mutex_unlock(&(val->guilty_spark));
				monitor(&philo[i], "died");
				pthread_mutex_lock(&(val->guilty_spark));
				val->sim_end = true;
				return((void)pthread_mutex_unlock(&(val->guilty_spark)));
			}
			i++;
		}
		if (check_all_philos_eaten(val, philo) == true)
			return (val->sim_end = true, (void)pthread_mutex_unlock(&(val->guilty_spark)));
		pthread_mutex_unlock(&(val->guilty_spark));
		usleep(1000);
	}
}
