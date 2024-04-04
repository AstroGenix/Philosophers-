/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_sim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberehov <dberehov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 10:22:47 by dberehov          #+#    #+#             */
/*   Updated: 2024/04/02 17:33:16 by dberehov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

long long	time_diff(long long past, long long pres)
{
	return (pres - past);
}
static void	check_all_philos_eaten(t_table *val, t_philo *philo)
{
	int	i;

	i = 0;
	while (val->max_meals != -1 && i < val->total_philo && philo[i].meal_count >= val->max_meals)
		i++;
	if (i == val->total_philo)
	{
		val->all_have_eaten = true;
		val->sim_end == true;
	}
}

void	catch_end_clause(t_table *val, t_philo *philo)
{
	int i;

	while (val->all_have_eaten == false)
	{
		i = 0;
		while (i < val->total_philo)
		{
			pthread_mutex_lock(&(val->guilty_spark));
			if (time_diff(philo[i].last_meal_time, get_current_time()) > val->time_to_die)
			{
				monitor(&philo[i], "died");
				pthread_mutex_lock(&(val->write_lock));
				val->sim_end = true;
				pthread_mutex_unlock(&(val->write_lock));
				pthread_mutex_unlock(&(val->guilty_spark));
				break ;
			}
			pthread_mutex_unlock(&(val->guilty_spark));
			i++;
		}
		if (val->sim_end == true)
			break ;
		pthread_mutex_lock(&(val->guilty_spark));
		check_all_philos_eaten(val, philo);
		pthread_mutex_unlock(&(val->guilty_spark));
	}
}
