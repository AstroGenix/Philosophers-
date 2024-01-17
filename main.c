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
	if (argn != 6)
		printf("Wrong arguments bozo!\n");
	else
	{
		printf("Number of Philosophers: %s\n", args[1]);
		printf("Time to die: %s\n", args[2]);
		printf("Time to eat: %s\n", args[3]);
		printf("Time to sleep: %s\n", args[4]);
		printf("N of times each philo must eat: %s\n", args[5]);
	}
	
}
