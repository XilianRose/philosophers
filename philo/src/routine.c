/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/04 15:42:34 by mstegema      #+#    #+#                 */
/*   Updated: 2024/02/01 20:05:51 by mstegema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	dying(t_philo *status, t_action action)
{
	pthread_mutex_lock(status->data_copy->fatal_lock);
	if (*(status->data_copy->fatality) == true)
	{
		pthread_mutex_unlock(status->data_copy->fatal_lock);
		return (true);
	}
	pthread_mutex_unlock(status->data_copy->fatal_lock);
	if (action != EATING && get_time(status->data_copy) - status->last_eaten >= \
	status->data_copy->die_time)
	{
		pthread_mutex_lock(&status->dead_lock);
		status->dead = true;
		pthread_mutex_unlock(&status->dead_lock);
		pthread_mutex_lock(status->data_copy->print_lock);
		printf("%zu %zu died\n", get_time(status->data_copy), status->id);
		pthread_mutex_unlock(status->data_copy->print_lock);
		return (true);
	}
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
		if (dying(status, SLEEPING) == true)
			return (KO);
		usleep(5);
	}
	return (OK);
}

static size_t	eating(t_philo *status)
{
	print_message(status, status->last_eaten, status->id, \
	"is eating\n");
	pthread_mutex_lock(&status->eaten_lock);
	status->times_eaten++;
	pthread_mutex_unlock(&status->eaten_lock);
	while (get_time(status->data_copy) - status->last_eaten < \
	status->data_copy->eat_time)
	{
		if (dying(status, EATING) == true)
		{
			pthread_mutex_unlock(status->left_chopstick);
			pthread_mutex_unlock(status->right_chopstick);
			return (KO);
		}
		usleep(5);
	}
	return (OK);
}


static size_t	grabbing(t_philo *status)
{
	pthread_mutex_lock(status->left_chopstick);
	if (dying(status, THINKING) == true)
		return (pthread_mutex_unlock(status->left_chopstick), KO);
	print_message(status, get_time(status->data_copy), \
	status->id, "has taken a fork\n");
	if (status->data_copy->total == 1)
	{
		while (1)
		{
			if (dying(status, THINKING) == true)
				return (pthread_mutex_unlock(status->left_chopstick), KO);
			usleep(5);
		}
	}
	pthread_mutex_lock(status->right_chopstick);
	if (dying(status, THINKING) == true)
		return (pthread_mutex_unlock(status->left_chopstick), \
		pthread_mutex_unlock(status->right_chopstick), KO);
	status->last_eaten = get_time(status->data_copy);
	print_message(status, get_time(status->data_copy), \
	status->id, "has taken a fork\n");
	if (eating(status) == KO)
		return (KO);
	return (pthread_mutex_unlock(status->left_chopstick), \
		pthread_mutex_unlock(status->right_chopstick), OK);
}

void	*routine(void *arg)
{
	t_philo	*status;

	status = (t_philo *)arg;
	if (status->id % 2 != 0)
		usleep(status->data_copy->eat_time * 500);
	while (1)
	{
		if (grabbing(status) == KO)
			return (NULL);
		if (sleeping(status) == KO)
			return (NULL);
		print_message(status, get_time(status->data_copy), \
		status->id, "is thinking\n");
		if (dying(status, THINKING) == true)
			return (NULL);
	}
	return (NULL);
}
