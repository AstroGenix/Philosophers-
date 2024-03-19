
#ifndef PHILOSOPHERS
# define PHILOSOPHERS

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

/*Fork struct*/
typedef struct	s_fork
{
	int				fork_id;
	pthread_mutex_t	fork;
}					t_fork;

/*Philosophers struct*/
typedef struct	s_philo
{
	int			id;
	int			meal_count;
	bool		full;
	suseconds_t	last_meal_time;
	t_fork		*r_fork;
	t_fork		*l_fork;
	pthread_t	thread_id;
	suseconds_t	start_time;
}				t_philo;

/*Table struct*/
typedef struct	s_args
{
	int				philo_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_meals;
	bool			sim_end;
	pthread_mutex_t	guilty_spark;
}							t_args;


//- - Functions
void	err_exit(char *s);
void	helper_print(void);
int		philo_start(int argn, char **args);
bool	arg_check(int argn, char **args);

bool	init_values(t_args *val, char **args);

#endif