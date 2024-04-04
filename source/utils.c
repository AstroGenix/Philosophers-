/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberehov <dberehov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 08:14:52 by dberehov          #+#    #+#             */
/*   Updated: 2024/03/20 08:14:52 by dberehov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

/**
 * Retrieves the current system time in milliseconds.
 * • Utilizes gettimeofday() to fetch the current time.
 * • Converts the time into milliseconds.
 *
 * @return The current time in milliseconds.
 */
int	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

/**
 * Validates the command line arguments for numeric integrity.
 * • Iterates through each character of the argument strings.
 * • Ensures that each character is a digit, indicating a valid number.
 * 
 * @param argn Number of command line arguments.
 * @param args Array of command line argument strings.
 * @return True if any non-numeric characters are found, false otherwise.
 */
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
			{
				err_exit("Invalid argument");
				return (true);
			}
			j++;
		}
		i++;
	}
	return (false);
}

/**
 * Prints a helper message detailing command usage and parameters.
 * • Provides an example command.
 * • Explains each parameter with its expected value.
 */
static void	helper_print(void)
{
	printf("./philo" G " 5 " Y " 800 " B " 200 " M " 300" C " 7 " RST"\n");
	printf(G " 5   " RST ": The number of philosophers\n");
	printf(Y " 800 " RST ": The time a philosopher will die if he dont eat\n");
	printf(B " 200 " RST ": The time it takes a philosopher to eat\n");
	printf(M " 300 " RST ": The time it takes a philosopher to sleep\n");
	printf(C " 7   " RST ": (optional) Number of times all the "
		"philosophers need to eat before terminating the program\n");
}

/**
 * Exits the program with an error message.
 * • Invokes helper_print() to provide command usage information.
 * • Displays the provided error message in red within an error box.
 * 
 * @param msg The error message to display upon exit.
 */
void	err_exit(char *msg)
{
	helper_print();
	printf("\e[41mError:\e[0m" R " %s\n" RST, msg);
	return ;
}

/**
 * Converts a string to an integer (atoi implementation).
 * • Ignores leading whitespace characters.
 * • Handles optional leading '+' or '-' for positive/negative numbers.
 * • Converts a sequence of digits into an integer value.
 * 
 * @param nptr The string to convert to an integer.
 * @return The converted integer value.
 */
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
