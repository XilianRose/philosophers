/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/19 14:17:12 by mstegema      #+#    #+#                 */
/*   Updated: 2024/02/01 19:35:38 by mstegema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	join_philos(t_data *data)
{
	size_t	i;

	i = 0;
	if (!data->philos)
		return ;
	while (i < data->total)
	{
		if (pthread_join(data->philos[i], NULL) < 0)
		{
			printf("Pthread join failure\n");
			return ;
		}
		i++;
	}
	free(data->philos);
	data->philos = NULL;
}

void	reset_status(t_philo *status, size_t max)
{
	size_t	i;

	i = 0;

	if (!status)
		return ;
	while (i < max)
	{
		free(status[i].data_copy);
		status[i].data_copy = NULL;
		pthread_mutex_destroy(&status[i].eaten_lock);
		pthread_mutex_destroy(&status[i].dead_lock);
		i++;
	}
	free(status);
	status = NULL;
	return ;
}

void	discard_chopsticks(t_data *data)
{
	size_t	i;

	i = 0;
	if (!data->chopsticks)
		return ;
	while (i < data->total)
	{
		pthread_mutex_destroy(&data->chopsticks[i]);
		i++;
	}
	free(data->chopsticks);
	data->chopsticks = NULL;
}

void	clean_exit(t_data *data, t_philo *status)
{
	join_philos(data);
	if (data->print_lock)
	{
		pthread_mutex_destroy(data->print_lock);
		free(data->print_lock);
		data->print_lock = NULL;
	}
	if (data->fatal_lock)
	{
		pthread_mutex_destroy(data->fatal_lock);
		free(data->fatal_lock);
		data->fatal_lock = NULL;
	}
	discard_chopsticks(data);
	reset_status(status, data->total);
	return ;
}
