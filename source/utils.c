#include "../include/philosophers.h"

//If input something other than numbers exit with true flag
bool	arg_check(int argn, char **args)
{
	int	i;
	int	j;

	i = 1;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if (args[i][j] < '0' || args[i][j] > '9')
				return (true);
			j++;
		}
		i++;
	}
	return (false);
}

//To help user with command
void	helper_print(void)
{
	/*Example: 5 800 200 200 7*/
	printf("Example: ./philo" G " 5 " Y " 800 " B " 200 " M " 300" C " 7 " RST"\n");
	printf(G " 5   " RST ": The number of philosophers\n");
	printf(Y " 800 " RST ": The time a philosopher will die if he don’t eat\n");
	printf(B " 200 " RST ": The time it takes a philosopher to eat\n");
	printf(M " 300 " RST ": The time it takes a philosopher to sleep\n");
	printf(C " 7   " RST ": (optional) Number of times all the "
		 "philosophers need to eat before terminating the program\n");
}

//String describes the error to exit program.
void	err_exit(char *s)
{
	helper_print();
	printf("\e[41mError:\e[0m" R " %s\n" RST, s);
	exit (1);
}

//Ripped atoi func from LIBFT - Convert char to int
int	ft_atoi(const char *nptr)
{
	int	i;
	int	ngtv;
	int	result;

	i = 0;
	ngtv = 1;
	result = 0;
	while (nptr[i] == ' ' || nptr[i] == '\n' || nptr[i] == '\t'
		|| nptr[i] == '\v' || nptr[i] == '\f' || nptr[i] == '\r')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			ngtv = -1;
		i++;
	}
	while (nptr[i] != '\0' && nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = (nptr[i] - '0') + (result * 10);
		i++;
	}
	return (result * ngtv);
}