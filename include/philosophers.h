/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberehov <dberehov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 09:57:31 by dberehov          #+#    #+#             */
/*   Updated: 2024/03/20 09:57:31 by dberehov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

//- - Libraries
# include <memory.h>	// memset()
# include <stdio.h>		// printf()
# include <stdlib.h>	// malloc(), free()
# include <unistd.h>	// write(), usleep()
# include <sys/time.h>	// gettimeofday()
# include <pthread.h>	// thread API
# include <stdbool.h>	// True || False

//- - ANSI Escape sequence for text colors
// https://gist.github.com/RabaDabaDoba/145049536f815903c79944599c6f952a
# define RST	"\033[0m"	/*White  */
# define R		"\033[31m"	/*Red    */
# define G		"\033[32m"	/*Green  */
# define Y		"\033[33m"	/*Yellow */
# define B		"\033[34m"	/*Blue   */
# define M		"\033[35m"	/*Magenta*/
# define C		"\033[36m"	/*Cyan   */

//- - Structures

/*Philosophers struct*/
typedef struct s_philo
{
	int				id;
	int				meal_count;
	int				last_meal_time;
	int				r_fork;
	int				l_fork;
	pthread_t		thread_id;
	struct s_table	*table;
}					t_philo;

/*Table struct*/
typedef struct s_table
{
	int				total_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_meals;
	int				all_have_eaten;
	bool			sim_end;
	long long		sim_start_time;
	pthread_mutex_t	guilty_spark;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	fork[300];
	t_philo			philo[300];
}					t_table;

//- - Functions
void		cleanup(t_table *val);
bool		create_threads(t_table *val);
bool		join_threads(t_table *val, t_philo *philo);
//end_sim.c
void		catch_end_clause(t_table *val, t_philo *philo);
long long	time_diff(long long past, long long pres);
//init.c
bool		init_values(t_table *val, char **args);
bool		init_fork(t_table *val);
void		init_philo(t_table *val);
//monitor.c
void		monitor(t_philo *philo, char *msg);
//routine.c
void		*routine(void *philo);
//utils.c
int			get_current_time(void);
bool		arg_check(char **args);
void		err_exit(char *s);
int			ft_atoi(const char *nptr);
#endif