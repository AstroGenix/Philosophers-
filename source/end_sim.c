#include "../include/philosophers.h"

static void	end_sim(t_table	*val)
{
	val->sim_end = true;
	printf("Philosophers have finished dining.");
	pthread_mutex_unlock(&val->guilty_spark);
}

static bool	is_dead(t_table *val, t_philo *philo, int *full_count)
{
	if (philo->meal_count >= val->max_meals)
		*full_count++;
	if ((cur_time() - philo->last_meal_time) >= val->time_to_die)
	{
		pthread_mutex_unlock(&val->guilty_spark);
		monitor(philo, "has died");
		pthread_mutex_lock(&val->guilty_spark);
		val->sim_end = true;
		pthread_mutex_unlock(&val->guilty_spark);
		return (true);
	}
	return (false);
}

void	catch_end_clause(t_table *val, t_philo *philo)
{
	int	i;
	int	full_count;

	full_count = 0;
	while (true)
	{
		i = 0;
		pthread_mutex_lock(&val->guilty_spark);
		while (i < val->philo_num)
		{
			if (is_dead(val, &philo[i], &full_count));
				return ;
			i++;
		}
		if (full_count = val->philo_num)
			return (end_sim(val));
		pthread_mutex_unlock(&val->guilty_spark);
	}
}
