#include "../include/philosophers.h"

//Initiate and check for valid values
bool	init_values(t_args *val, char **args)
{
	val->philo_num = ft_atoi(args[1]);
	val->time_to_die = ft_atoi(args[2]);
	val->time_to_eat = ft_atoi(args[3]);
	val->time_to_sleep = ft_atoi(args[4]);
	if (args[5])
		val->max_meals = ft_atoi(args[5]);
	else
		val->max_meals = -1;
	if (val->philo_num == 0 || val->max_meals == 0)
		return (true);
	if (pthread_mutex_init(&val->guilty_spark, NULL) != 0)
		err_exit("Mutex initation failed [init_values()]");
	val->sim_end = false;
	return (false);
}

/*
pthread_mutex_t init_forks(char **args)
{
    var fork = create fork (size of pthread_mutex_t * num_philo);
    check for error creation
    Loop (until num of philo)
    {
        init fork;
        check for fork init error;
    }
    return fork
}
*/