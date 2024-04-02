#include "../include/philosophers.h"

static void	end_sim(t_table	*val)
{
	val->sim_end = true;
	pthread_mutex_lock(&val->write_lock);
	printf("Philosophers have finished dining\n");
	pthread_mutex_unlock(&val->write_lock);
	pthread_mutex_unlock(&val->guilty_spark);
}

static bool	is_dead(t_table *val, t_philo *philo)
{
	if (((cur_time() - philo->last_meal_time) >= philo->table->time_to_die))
	{
		pthread_mutex_unlock(&val->guilty_spark);
		monitor(philo, "died");
		pthread_mutex_lock(&val->guilty_spark);
		val->sim_end = true;
		pthread_mutex_unlock(&val->guilty_spark);
		return (true);
	}
	return (false);
}

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
			if (philo[i].meal_count < philo->table->max_meals || val->max_meals < 0)
				full_count = false;
			if (is_dead(val, &philo[i]))
				return ;
		}
		if (full_count)
			return (end_sim(val));
		pthread_mutex_unlock(&val->guilty_spark);
	}
}
