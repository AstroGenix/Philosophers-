/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberehov <dberehov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:55:02 by dberehov          #+#    #+#             */
/*   Updated: 2024/03/20 13:53:32 by dberehov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

//The routine philosophers must abide by
void	*routine(void *philo)
{
	t_philo *me;
    
    me = (t_philo *)philo;
    if (me->table->philo_num = 1)
    {
        monitor(philo);
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
        monitor(philo);
	}
	return (NULL);
}