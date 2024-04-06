#include "../include/philosophers.h"

/**
 * Makes the philosopher nap for a specified time.
 * The function waits until the specified time has passed.
 * 
 * @param time The time to nap in milliseconds.
 */
bool	nap(t_philo *me)
{
	if (monitor(me, "is sleeping"))
		return (true);
	usleep(me->table->time_to_sleep * 1000);
	return (false);
}

static bool	grab_fork(t_philo *me)
{
	t_table	*val;

	val = me->table;
	pthread_mutex_lock(&(val->fork[me->l_fork]));
	if (monitor(me, "has taken a fork"))
		return (pthread_mutex_unlock(&(val->fork[me->l_fork])),true);
	pthread_mutex_lock(&(val->fork[me->r_fork]));
	if (monitor(me, "has taken a fork"))
		return (pthread_mutex_unlock(&(val->fork[me->r_fork])),
			pthread_mutex_unlock(&(val->fork[me->l_fork])),true);
	return (false);
}

/**
 * Represents a philosopher's eating action.
 * The philosopher takes forks, eats, then drops forks.
 * 
 * @param philo The philosopher struct.
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
