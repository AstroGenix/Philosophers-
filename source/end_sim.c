#include "../include/philosophers.h"

static void	end_sim(t_table	*val)
{
	val->sim_end = true;
	printf("Philosophers have finished dining\n");
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
	int	j = 0;

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
		{
			while (j < philo->table->philo_num)
			{
				//here
				printf("Philo %i has eaten %i meals (max: %i)\n", philo[j].id, philo[j].meal_count, philo->table->max_meals);
				j++;
			}
			return (end_sim(val));
		}
		pthread_mutex_unlock(&val->guilty_spark);
	}
}

/*void	*check_meal_completion(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	int		i;
	int j = 0;
	bool	all_philos_satisfied;

	while (true)
	{
		i = 0;
		all_philos_satisfied = true;
		pthread_mutex_lock(&philo->table->guilty_spark);
		while (i < philo->table->philo_num)
		{
			if (philo[i].meal_count < philo->table->max_meals)
			{
				all_philos_satisfied = false;
				break ;
			}
			i++;
		}
		pthread_mutex_unlock(&philo->table->guilty_spark);
		if (all_philos_satisfied)
		{
			while (j < philo->table->philo_num)
			{
				//here
				printf("Philo %i has eaten %i meals (max: %i)\n", philo[j].id, philo[j].meal_count, philo->table->max_meals);
				j++;
			}
			pthread_mutex_lock(&philo->table->guilty_spark);
            philo->table->sim_end = true;
            pthread_mutex_unlock(&philo->table->guilty_spark);
			break ;
		}
		usleep(100);
	}
}*/
