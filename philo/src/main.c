/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/03 15:47:20 by mstegema      #+#    #+#                 */
/*   Updated: 2024/01/11 14:42:00 by mstegema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_info	*info;

	info = NULL;
	if (gettimeofday(time, NULL) != 0)
		return (KO);
	if (argc < 4)
		return (printf("Not enough arguments given\n"), 1);
	else if (argc > 5)
		return (printf("Too many arguments given\n"), 1);
	if (parse_arguments(argc, argv, info) == 0)
		return (printf("Invalid arguments given\n"), 1);
	return (OK);
}
