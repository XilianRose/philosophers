/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   actions.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/04 15:42:34 by mstegema      #+#    #+#                 */
/*   Updated: 2024/01/11 14:39:56 by mstegema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	grab(void *ptr)
{
	t_info	*info;
	size_t	ms;
	size_t	left;
	size_t	right;

	info = (t_info *)ptr;
	left = x;
	right = (left + 1) % info->no_philo;
	if (pthread_mutex_lock(&info->chopsticks[left]))
	{
		ms = get_time(info);
		printf("%i X has taken a chopstick", ms);
		if (!pthread_mutex_lock(&info->chopsticks[right]))
			pthread_mutex_unlock(&info->chopsticks[left]);
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
