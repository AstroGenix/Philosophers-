/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberehov <dberehov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:55:02 by dberehov          #+#    #+#             */
/*   Updated: 2024/03/20 14:02:10 by dberehov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void nap(t_philo *philo)
{
    monitor(philo);
    usleep(philo->table->time_to_sleep * 1000);
}

static void eat(t_philo *philo)
{

}

//The routine philosophers must abide by
void	*routine(void *philo)
{
	t_philo *me;
    
    me = (t_philo *)philo;
    if (me->table->philo_num = 1)
    {
        monitor(me);
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
        monitor(me);
	}
	return (NULL);
}