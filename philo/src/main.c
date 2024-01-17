/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/03 15:47:20 by mstegema      #+#    #+#                 */
/*   Updated: 2024/01/17 15:23:24 by mstegema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	*data;

	data = NULL;
	if (gettimeofday(data->start_time, NULL) != OK)
		return ((printf("TOD failure\n"), KO));
	if (argc < 4 || argc > 5)
		return (printf("Invalid number of arguments given\n"), KO);
	if (parsing(argc, argv, data) == KO)
		return (printf("Invalid arguments given\n"), KO);
	if (init_data(argc, argv, data) == KO)
		return (printf("Malloc failure\n"), KO);
	return (OK);
}
