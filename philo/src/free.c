/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/19 14:17:12 by mstegema      #+#    #+#                 */
/*   Updated: 2024/01/19 16:56:40 by mstegema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	free_data_copy(t_data *data, t_philo *status, size_t max)
{
	size_t	i;

	i = 0;
	if (!status)
		return ;
	while (i < max || i < data->total)
	{
		if (!status[i].data_copy)
			return ;
		free(status[i].data_copy);
		status[i].data_copy = NULL;
		i++;
	}
	return ;
}

void	reset_status(t_data *data, t_philo *status, size_t max)
{
	size_t	i;

	i = 0;

	if (!status)
		return ;
	free_data_copy(status->data_copy, status, max);
	while (i < data->total)
	{
		pthread_mutex_destroy(&status[i].eaten_lock);
		pthread_mutex_destroy(&status[i].fatal_lock);
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
	pthread_mutex_destroy(data->print_lock);
	discard_chopsticks(data);
	reset_status(data, status, data->total);
	if (!data->philos)
		return ;
	free(data->philos);
	data->philos = NULL;
	return ;
}
