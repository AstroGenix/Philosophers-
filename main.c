/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberehov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 09:31:34 by dberehov          #+#    #+#             */
/*   Updated: 2024/01/17 09:31:35 by dberehov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philosophers.h"

int	main(int argn, char *args[])
{
    t_table table;
	if  ((argn != 5 && argn != 6) || (arg_check(argn, args) == true))
	{
		helper_print();
		err_exit("Incorrect arguments");
	}
	if (philo(argn, args) != 0)
		err_exit("Error in philo");
	return (0);
}

int	philo(int argn, char **args)
{
	return (0);
}
