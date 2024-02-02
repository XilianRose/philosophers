/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/04 15:42:34 by mstegema      #+#    #+#                 */
/*   Updated: 2024/02/02 18:31:44 by mstegema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	dying(t_philo *status)
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
	print_message(status, start_time, status->id, "is sleeping\n");
	while (get_time(status->data_copy) - start_time < \
	status->data_copy->sleep_time)
	{
		if (dying(status) == true)
			return (KO);
		usleep(5);
	}
	return (OK);
}

static size_t	eating(t_philo *status)
{
	pthread_mutex_lock(&status->eaten_lock);
	status->last_eaten = get_time(status->data_copy);
	pthread_mutex_unlock(&status->eaten_lock);
	print_message(status, status->last_eaten, status->id, \
	"is eating\n");
	while (get_time(status->data_copy) - status->last_eaten < \
	status->data_copy->eat_time)
	{
		if (dying(status) == true)
		{
			pthread_mutex_unlock(status->left_chopstick);
			pthread_mutex_unlock(status->right_chopstick);
			return (KO);
		}
		usleep(5);
	}
	pthread_mutex_lock(&status->eaten_lock);
	status->times_eaten++;
	pthread_mutex_unlock(&status->eaten_lock);
	return (OK);
}

static size_t	grabbing(t_philo *status)
{
	pthread_mutex_lock(status->left_chopstick);
	if (dying(status) == true)
		return (pthread_mutex_unlock(status->left_chopstick), KO);
	print_message(status, get_time(status->data_copy), \
	status->id, "has taken a fork\n");
	if (status->data_copy->total == 1)
	{
		while (1)
		{
			if (dying(status) == true)
				return (pthread_mutex_unlock(status->left_chopstick), KO);
			usleep(5);
		}
	}
	pthread_mutex_lock(status->right_chopstick);
	if (dying(status) == true)
		return (pthread_mutex_unlock(status->left_chopstick), \
		pthread_mutex_unlock(status->right_chopstick), KO);
	print_message(status, get_time(status->data_copy), \
	status->id, "has taken a fork\n");
	if (eating(status) == KO)
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
		if (grabbing(status) == KO)
			return (NULL);
		if (sleeping(status) == KO)
			return (NULL);
		print_message(status, get_time(status->data_copy), \
		status->id, "is thinking\n");
		if (dying(status) == true)
			return (NULL);
	}
	return (NULL);
}
