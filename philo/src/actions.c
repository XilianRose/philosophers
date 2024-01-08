/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   actions.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/04 15:42:34 by mstegema      #+#    #+#                 */
/*   Updated: 2024/01/08 15:13:41 by mstegema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	grab(void *ptr)
{
	t_info	*info;
	size_t	ms;

	info = (t_info *)ptr;
	if (pthread_mutex_lock(&info->chopsticks[x]))
	{
		ms = get_time(info);
		printf("%i X has taken a chopstick", ms);
		if (!pthread_mutex_lock(&info->chopsticks[(x + 1) % info->no_philo]))
			pthread_mutex_unlock(&info->chopsticks[x]);
		else
		{
			ms = get_time(info);
			printf("%i X has taken a chopstick", ms);
		}
	}
	eat(info);
}

void	eat(void *ptr)
{
	t_info	*info;
	size_t	ms;

	info = (t_info *)ptr;
	ms = get_time(info);
	printf("%i X is eating", ms);
	usleep(info->eat);
}

void	sleep(void *ptr)
{
	t_info	*info;
	size_t	ms;

	info = (t_info *)ptr;
	ms = get_time(info);
	printf("%i X is sleeping", ms);
	usleep(info->sleep);
}

void	think(void *ptr)
{
	t_info	*info;
	size_t	ms;

	info = (t_info *)ptr;
	ms = get_time(info);
	printf("%i X is thinking", ms);
}
