/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/03 15:47:20 by mstegema      #+#    #+#                 */
/*   Updated: 2024/02/05 11:07:13 by mstegema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	is_everyone_alive(t_data *data, t_philo *status)
{
	size_t	i;

	i = 0;
	while (i < data->total)
	{
		pthread_mutex_lock(&status[i].eaten_lock);
		if (get_time(status->data_copy) - status[i].last_eaten >= \
		data->die_time)
		{
			pthread_mutex_lock(data->fatal_lock);
			*(data->fatality) = true;
			pthread_mutex_unlock(data->fatal_lock);
			pthread_mutex_lock(status->data_copy->print_lock);
			printf("%zu %zu died\n", get_time(status->data_copy), status[i].id);
			pthread_mutex_unlock(status->data_copy->print_lock);
			pthread_mutex_unlock(&status[i].eaten_lock);
			return (false);
		}
		pthread_mutex_unlock(&status[i].eaten_lock);
		i++;
	}
	return (true);
}

static bool	is_everyone_full(t_data *data, t_philo *status)
{
	size_t	i;

	i = 0;
	while (i < data->total)
	{
		pthread_mutex_lock(&status[i].eaten_lock);
		if (status[i].times_eaten < data->full_at)
		{
			pthread_mutex_unlock(&status[i].eaten_lock);
			return (false);
		}
		pthread_mutex_unlock(&status[i].eaten_lock);
		i++;
	}
	pthread_mutex_lock(data->fatal_lock);
	*(data->fatality) = true;
	pthread_mutex_unlock(data->fatal_lock);
	return (true);
}

static void	welfare_check(t_data *data, t_philo *status)
{
	size_t	i;

	i = 0;
	while (1)
	{
		if (i == data->total)
			i = 0;
		if (is_everyone_alive(data, status) == false)
			return ;
		if (data->full_at > 0 && is_everyone_full(data, status) == true)
			return ;
		usleep(data->die_time);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data		data;
	t_philo		*status;

	status = NULL;
	if (argc < 5 || argc > 6)
		return (printf("Invalid number of arguments given\n"), KO);
	if (parsing(argc, argv) == KO)
		return (printf("Invalid arguments given\n"), KO);
	status = init_all(argc, argv, &data, status);
	if (status == NULL)
		return (KO);
	welfare_check(&data, status);
	clean_exit(&data, status);
	return (OK);
}
