/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/03 15:47:20 by mstegema      #+#    #+#                 */
/*   Updated: 2024/01/19 16:37:39 by mstegema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	everyone_full(t_data *data, t_philo *status)
{
	size_t	i;

	i = 0;
	while (i < data->total)
	{
		pthread_mutex_lock(&status[i].eaten_lock);
		if (status[i].times_eaten < data->full_at)
			return (pthread_mutex_unlock(&status[i].eaten_lock), false);
		pthread_mutex_unlock(&status[i].eaten_lock);
		i++;
	}
	return (true);
}

static size_t	welfare_check(t_data *data, t_philo *status)
{
	size_t	i;

	i = 0;
	while (1)
	{
		pthread_mutex_lock(&status[i].fatal_lock);
		if (status[i].fatality == true)
		{
			i = 0;
			pthread_mutex_unlock(&status[i].fatal_lock);
			while (i < data->total)
			{
				pthread_mutex_lock(&status[i].fatal_lock);
				status[i].fatality == true;
				pthread_mutex_unlock(&status[i++].fatal_lock);
			}
			return (KO);
		}
		pthread_mutex_unlock(&status[i].fatal_lock);
		if (everyone_full(data, status) == true)
			return (OK);
		i++;
		if (i == data->total)
			i = 0;
	}
}

int	main(int argc, char **argv)
{
	t_data		*data;
	t_philo		*status;

	data = NULL;
	if (argc < 4 || argc > 5)
		return (printf("Invalid number of arguments given\n"), KO);
	if (parsing(argc, argv) == KO)
		return (printf("Invalid arguments given\n"), KO);
	if (init_all(argc, argv, data, status) == KO)
		return (KO);
	welfare_check(data, status);
	clean_exit(data, status);
	return (OK);
}
