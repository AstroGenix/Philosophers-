/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberehov <dberehov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:06:57 by dberehov          #+#    #+#             */
/*   Updated: 2024/04/02 11:16:28 by dberehov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

/**
 * Logs a timestamped action message for a philosopher with color-coded output
 * for clarity.
 * • Colors the philosopher's ID based on a cycle of ANSI colors for easy
 *   differentiation.
 * • The timestamp is relative to the simulation's start, providing the timing
 *   context of the action.
 *
 * @param i The philosopher's ID, used to identify and colorcode the log entry.
 * @param msg The action or event to log (e.g., "has taken a fork").
 * @param time The time elapsed since the simulation started, in milliseconds.
 */
static void	log_action(int i, char *msg, suseconds_t time)
{
	const char	*color[7] = {"\e[1;91m", "\e[1;92m", "\e[1;93m", "\e[1;94m",
		"\e[1;95m", "\e[1;96m", "\e[1;97m"};

	printf("\e[1;97m%ld \e[0m", time);
	printf("%s%i ", color[i % 7], i);
	printf("\e[1;97m%s\e[0m\n", msg);
}

/**
 * Monitors and logs a philosopher's action with a timestamp if the simulation
 * is ongoing.
 * • Ensures thread safety by locking a dedicated mutex for logging actions.
 * • Checks if the simulation is still running to avoid logging actions after
 *   its conclusion.
 * • Calculates the action's timestamp relative to the simulation's start for
 *   contextual timing.
 *
 * @param philo The philosopher struct including the philosopher's ID and
 * pointer to the table struct.
 * @param msg The message describing the philosopher's action to log.
 */
void	monitor(t_philo *philo, char *msg)
{
	int	time;

	pthread_mutex_lock(&philo->table->write_lock);
	if (philo->table->sim_end)
	{
		pthread_mutex_unlock(&philo->table->write_lock);
		return ;
	}
	time = get_current_time() - philo->table->sim_start_time;
	log_action(philo->id, msg, time);
	pthread_mutex_unlock(&philo->table->write_lock);
}
