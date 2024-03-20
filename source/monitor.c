/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberehov <dberehov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:06:57 by dberehov          #+#    #+#             */
/*   Updated: 2024/03/20 16:08:40 by dberehov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

//Outputs the text message
void	log_occur(int i, char *msg, long int time)
{
	const char *color[7] = {"\e[1;91m", "\e[1;92m", "\e[1;93m", "\e[1;94m",
							"\e[1;95m", "\e[1;96m", "\e[1;97m"};
	printf("\e[1;97m%ld \e[0m\t", time);
	if (i > 6)
		if (i % 7 == 0)
			printf("%s%i ",color[0], i);
		else if (i % 5 == 0)
			printf("%s%i ",color[1], i);
		else if (i % 3 == 0)
			printf("%s%i ",color[2], i);
		else if (i % 2 == 0)
			printf("%s%i ",color[3], i);
		else
			printf("%s%i ",color[4], i);
	else
		printf("%s%i ",color[i], i);
	printf("\e[1;97m%s\e[0m\n", msg);
}

//
void	monitor(t_philo *philo, char *msg)
{
	suseconds_t	time;

	pthread_mutex_lock(&philo->table->guilty_spark);
	if (philo->table->sim_end)
	{
		pthread_mutex_unlock(&philo->table->guilty_spark);
		return ;
	}
	time = cur_time() - philo->start_time;
	log_occur(philo->id, msg, time);
	pthread_mutex_unlock(&philo->table->guilty_spark);
}