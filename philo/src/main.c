/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/03 15:47:20 by mstegema      #+#    #+#                 */
/*   Updated: 2024/01/18 17:14:45 by mstegema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data		*data;
	pthread_t	*philos;

	data = NULL;
	if (argc < 4 || argc > 5)
		return (printf("Invalid number of arguments given\n"), KO);
	if (parsing(argc, argv) == KO)
		return (printf("Invalid arguments given\n"), KO);
	if (init_data(argc, argv, data, philos) == KO)
		return (KO);
	return (OK);
}
