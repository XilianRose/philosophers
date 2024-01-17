/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/04 15:42:34 by mstegema      #+#    #+#                 */
/*   Updated: 2024/01/17 16:10:19 by mstegema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	grab(void *ptr)
{
	t_data	*data;
	size_t	ms;
	size_t	left;
	size_t	right;

	data = (t_data *)ptr;
	left = x;
	right = (left + 1) % data->no_philo;
	if (pthread_mutex_lock(&data->chopsticks[left]))
	{
		ms = get_time(data);
		printf("%i X has taken a chopstick", ms);
		if (!pthread_mutex_lock(&data->chopsticks[right]))
			pthread_mutex_unlock(&data->chopsticks[left]);
		else
		{
			ms = get_time(data);
			printf("%i X has taken a chopstick", ms);
		}
	}
	eat(data);
}

void	eat(void *ptr)
{
	t_data	*data;
	size_t	ms;

	data = (t_data *)ptr;
	ms = get_time(data);
	printf("%i X is eating", ms);
	usleep(data->eat);
}

void	sleep(void *ptr)
{
	t_data	*data;
	size_t	ms;

	data = (t_data *)ptr;
	ms = get_time(data);
	printf("%i X is sleeping", ms);
	usleep(data->sleep);
}

void	think(void *ptr)
{
	t_data	*data;
	size_t	ms;

	data = (t_data *)ptr;
	ms = get_time(data);
	printf("%i X is thinking", ms);
}

void	routine(void)
{
	return ;
}
