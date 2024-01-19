/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/04 15:42:34 by mstegema      #+#    #+#                 */
/*   Updated: 2024/01/19 17:18:31 by mstegema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	dying(t_philo *status, t_action action)
{
	pthread_mutex_lock(&status->fatal_lock);
	if (status->fatality == true)
	{
		pthread_mutex_unlock(&status->fatal_lock);
		return (true);
	}
	if (action != EATING && (status->data_copy) - status->last_eaten >= \
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
	if (pthread_mutex_lock(status->left_chopstick))
	{
		print_message(status->data_copy, get_time(status->data_copy), \
		status->id, "grabbed a chopstick\n");
		if (dying(status, EATING) == true)
			return (pthread_mutex_unlock(status->left_chopstick), KO);
		if (pthread_mutex_lock(status->right_chopstick))
		{
			status->last_eaten = get_time(status->data_copy);
			print_message(status->data_copy, get_time(status->data_copy), \
			status->id, "grabbed a chopstick\n");
			print_message(status->data_copy, status->last_eaten, status->id, \
			"is eating\n");
			while (get_time(status->data_copy) - status->last_eaten < \
			status->data_copy->eat_time)
			{
				if (dying(status, EATING) == true)
					return (KO);
				usleep(5);
			}
			pthread_mutex_unlock(status->left_chopstick);
			pthread_mutex_unlock(status->right_chopstick);
		}
	}
	return ;
}

void	routine(void *arg)
{
	t_philo	*status;

	status = (t_philo *)arg;
	if (status->data_copy->total % 2 != 0)
		usleep(status->data_copy->eat_time / 2);
	while (status->fatality == false)
	{
		if (eating(status) == KO)
			return ;
		if (sleeping(status) == KO)
			return ;
		print_message(status->data_copy, get_time(status->data_copy), \
		status->id, "is thinking\n");
	}
	return ;
}
