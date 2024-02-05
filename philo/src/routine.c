/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/04 15:42:34 by mstegema      #+#    #+#                 */
/*   Updated: 2024/02/05 11:05:57 by mstegema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	is_ending(t_philo *status)
{
	pthread_mutex_lock(status->data_copy->fatal_lock);
	if (*(status->data_copy->fatality) == true)
	{
		pthread_mutex_unlock(status->data_copy->fatal_lock);
		return (true);
	}
	pthread_mutex_unlock(status->data_copy->fatal_lock);
	return (false);
}

static size_t	sleeping(t_philo *status)
{
	size_t	start_time;

	start_time = get_time(status->data_copy);
	print_message(status, start_time, "is sleeping\n");
	while (get_time(status->data_copy) - start_time < \
	status->data_copy->sleep_time)
	{
		if (is_ending(status) == true)
			return (KO);
		usleep(status->data_copy->die_time);
	}
	return (OK);
}

static size_t	_eating(t_philo *status)
{
	pthread_mutex_lock(&status->eaten_lock);
	status->last_eaten = get_time(status->data_copy);
	pthread_mutex_unlock(&status->eaten_lock);
	print_message(status, status->last_eaten, "is eating\n");
	while (get_time(status->data_copy) - status->last_eaten < \
	status->data_copy->eat_time)
	{
		if (is_ending(status) == true)
		{
			pthread_mutex_unlock(status->left_chopstick);
			pthread_mutex_unlock(status->right_chopstick);
			return (KO);
		}
		usleep(status->data_copy->die_time);
	}
	pthread_mutex_lock(&status->eaten_lock);
	status->times_eaten++;
	pthread_mutex_unlock(&status->eaten_lock);
	return (OK);
}

static size_t	eating(t_philo *status)
{
	pthread_mutex_lock(status->left_chopstick);
	if (is_ending(status) == true)
		return (pthread_mutex_unlock(status->left_chopstick), KO);
	print_message(status, get_time(status->data_copy), "has taken a fork\n");
	if (status->data_copy->total == 1)
	{
		while (1)
		{
			if (is_ending(status) == true)
				return (pthread_mutex_unlock(status->left_chopstick), KO);
			usleep(status->data_copy->die_time);
		}
	}
	pthread_mutex_lock(status->right_chopstick);
	if (is_ending(status) == true)
		return (pthread_mutex_unlock(status->left_chopstick), \
		pthread_mutex_unlock(status->right_chopstick), KO);
	print_message(status, get_time(status->data_copy), "has taken a fork\n");
	if (_eating(status) == KO)
		return (KO);
	return (pthread_mutex_unlock(status->right_chopstick), \
		pthread_mutex_unlock(status->left_chopstick), OK);
}

void	*routine(void *arg)
{
	t_philo			*status;
	pthread_mutex_t	*temp;

	status = (t_philo *)arg;
	if (status->id % 2 != 0)
	{
		temp = status->left_chopstick;
		status->left_chopstick = status->right_chopstick;
		status->right_chopstick = temp;
	}
	while (1)
	{
		if (eating(status) == KO)
			return (NULL);
		if (sleeping(status) == KO)
			return (NULL);
		print_message(status, get_time(status->data_copy), "is thinking\n");
		if (is_ending(status) == true)
			return (NULL);
		usleep(status->last_eaten + status->data_copy->die_time \
		- get_time(status->data_copy));
	}
	return (NULL);
}
