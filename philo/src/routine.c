/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/04 15:42:34 by mstegema      #+#    #+#                 */
/*   Updated: 2024/01/31 12:38:10 by mstegema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//	if ((status->data_copy->full_at != 0 && status->times_eaten < \
//	status->data_copy->full_at) && (action != EATING && \
//	(get_time(status->data_copy) - status->last_eaten) >= \
//	status->data_copy->die_time))

static bool	dying(t_philo *status, t_action action)
{
	pthread_mutex_lock(&status->fatal_lock);
	if (status->fatality == true)
	{
		pthread_mutex_unlock(&status->fatal_lock);
		return (true);
	}
	if (action != EATING && get_time(status->data_copy) - status->last_eaten >= \
	status->data_copy->die_time)
	{
		print_message(status->data_copy, get_time(status->data_copy), \
		status->id, "died\n");
		status->fatality = true;
		pthread_mutex_unlock(&status->fatal_lock);
		return (true);
	}
	pthread_mutex_unlock(&status->fatal_lock);
	return (false);
}

static size_t	sleeping(t_philo *status)
{
	size_t	start_time;

	start_time = get_time(status->data_copy);
	print_message(status->data_copy, start_time, status->id, "is sleeping\n");
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
	print_message(status->data_copy, status->last_eaten, status->id, \
	"is eating\n");
	pthread_mutex_lock(&status->eaten_lock);
	status->times_eaten++;
	pthread_mutex_unlock(&status->eaten_lock);
	while (get_time(status->data_copy) - status->last_eaten < \
	status->data_copy->eat_time)
	{
		if (dying(status, EATING) == true)
			return (KO);
		usleep(5);
	}
	return (OK);
}

static size_t	grabbing(t_philo *status)
{
	if (pthread_mutex_lock(status->left_chopstick))
	{
		print_message(status->data_copy, get_time(status->data_copy), \
		status->id, "grabbed a chopstick\n");
		if (pthread_mutex_lock(status->right_chopstick))
		{
			status->last_eaten = get_time(status->data_copy);
			print_message(status->data_copy, get_time(status->data_copy), \
			status->id, "grabbed a chopstick\n");
			if (eating(status) == KO)
				return (KO);
			pthread_mutex_unlock(status->left_chopstick);
			pthread_mutex_unlock(status->right_chopstick);
		}
	}
	return (OK);
}

void	*routine(void *arg)
{
	t_philo	*status;

	status = (t_philo *)arg;
	if (status->id % 2 != 0)
		usleep(status->data_copy->eat_time / 2);
	while (status->fatality == false)
	{
		if (grabbing(status) == KO)
			return (NULL);
		if (sleeping(status) == KO)
			return (NULL);
		print_message(status->data_copy, get_time(status->data_copy), \
		status->id, "is thinking\n");
	}
	return (NULL);
}
