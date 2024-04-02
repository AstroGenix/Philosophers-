/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberehov <dberehov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:06:57 by dberehov          #+#    #+#             */
/*   Updated: 2024/04/02 10:04:37 by dberehov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

/**
 * Outputs a timestamped message for a philosopher's action, using colored text
 *   for easier identification.
 * The timestamp is relative to the philosopher's start time in the simulation,
 *   providing context for the action's timing.
 * Colors are assigned cyclically based on the philosopher's ID to differentiate
 *   output between philosophers.
 *
 * ANSI escape sequences are used for coloring:
 * - The timestamp and message are displayed in white.
 * - The philosopher's ID is displayed in a color determined by cycling through 
 *  a preset array of colors.
 *
 * @param i The philosopher's ID, used for color coding and identifying the
 *   philosopher in the log.
 * @param msg The action or message to log (e.g., "grabbed left fork").
 * @param time The relative time (in milliseconds) at which the action
 *   occurred, since the start of the simulation.
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
 * Logs an action taken by a philosopher with a timestamp.
 * 
 * This function ensures that the action is logged only if the simulation
 * is still running (sim_end is false). It locks the simulation-wide mutex
 * (guilty_spark) to safely check the simulation's end condition and to
 * serialize access to shared resources (e.g., logging output) for thread
 * safety.
 * The function calculates the time since the philosopher's start time to
 * provide a relative timestamp for when the action occurred.
 *
 * @param philo The philosopher who is performing the action.
 * @param msg The message to log, describing the action taken.
 */
void	monitor(t_philo *philo, char *msg)
{
	int	time;

	pthread_mutex_lock(&philo->table->write_lock);// Lock the simulation-wide mutex to ensure thread-safe access.
	if (philo->table->sim_end)// If the simulation has ended, unlock the mutex and return early.
	{
		pthread_mutex_unlock(&philo->table->write_lock);
		return ;
	}
	time = cur_time() - philo->table->sim_start_time;// Calculate the time since the philosopher's start time.
	log_action(philo->id, msg, time); // Log the action with a relative timestamp.
	pthread_mutex_unlock(&philo->table->write_lock);// Unlock the simulation-wide mutex.
}
