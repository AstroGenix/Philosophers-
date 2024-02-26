
#ifndef PHILOSOPHERS
# define PHILOSOPHERS

//Libraries
# include <memory.h>	// memset()
# include <stdio.h>		// printf()
# include <stdlib.h>	// malloc(), free()
# include <unistd.h>	// write(), usleep()
# include <sys/time.h>	// gettimeofday()
# include <pthread.h>	// thread API
# include <stdbool.h>	// True || False

//ANSI Escape sequence for text colors
# define RST	"\033[0m"	/*White  */
# define R		"\033[31m"	/*Red    */
# define G		"\033[32m"	/*Green  */
# define Y		"\033[33m"	/*Yellow */
# define B		"\033[34m"	/*Blue   */
# define M		"\033[35m"	/*Magenta*/
# define C		"\033[36m"	/*Cyan   */

//Structures
typedef struct s_philo
{
	int		id;
	int		meals;
	bool	full;
	int		last_meal_time;
}				t_philo;

//Functions
void	err_exit(char *s);
void	helper_print(void);
int		philo(int argn, char **args);
bool	arg_check(int argn, char **args);

#endif