
#ifndef PHILOSOPHERS
# define PHILOSOPHERS

//Libraries
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

//Functions
void	err_out(char *s);
void	helper_print(void);
int		philo(int argn, char *args[]);
int		input_check(int argn, char *args[]);

#endif