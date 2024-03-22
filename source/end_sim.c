#include "../include/philosophers.h"

static inline bool	starved(t_philo *philo)
{
	return (((cur_time() - philo->last_meal_time)
			>= philo->table->time_to_die));
}

static void	end_sim(t_table	*val)
{
	val->sim_end = true;
	printf("Philosophers have finished dining.");
	pthread_mutex_unlock(&val->guilty_spark);
}

static bool	is_dead(t_table *val, t_philo *philo, int *full_count)
{
	//printf("val->max_meals: %i > 0 && philo->meal_count : %i >=  %i :val->max_meals\n", val->max_meals, philo->meal_count, val->max_meals);
	if (val->max_meals > 0 && philo->meal_count >= val->max_meals)
	{
		*full_count++;
	}
	if (starved(philo))
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
	int	i;
	int	full_count;

	full_count = 0;
	while (true)
	{
		i = -1;
		pthread_mutex_lock(&val->guilty_spark);
		while (++i < val->philo_num)
		{
			//printf("Philo %i | meal n: %i < %i\n", val->philo_num, philo->meal_count, full_count);
			if (is_dead(val, &philo[i], &full_count))
				return ;
		}
        //printf("Meal needed: %i | meal n: %i\n", val->philo_num, full_count);
		if (full_count == val->philo_num)
			return (end_sim(val));
		pthread_mutex_unlock(&val->guilty_spark);
	}
}
