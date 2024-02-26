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
	
	if (input_check(argn, args) != 0)
	{	
		helper_print();
		err_out("Wrong input");
	}
	if (philo(argn, args) != 0)
		err_out("Error in philo");
	return (0);
}

int	input_check(int argn, char *args[])
{
	return (1);
}

int	philo(int argn, char *args[])
{
	return (0);
}
