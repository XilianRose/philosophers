/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/17 14:15:36 by mstegema      #+#    #+#                 */
/*   Updated: 2024/01/31 12:31:33 by mstegema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static size_t	init_philos(t_data *data, t_philo *status)
{
	size_t	i;

	i = 0;
	data->philos = (pthread_t *)malloc((data->total) * sizeof(pthread_t));
	if (!data->philos)
		return (clean_exit(data, status), KO);
	while (i < data->total)
	{
		pthread_create(&data->philos[i], NULL, &routine, (void *)&status[i]);
		i++;
	}
	return (OK);
}

t_data	*copy_data(t_data *data)
{
	t_data	*temp;

	temp = (t_data *)malloc(1 * sizeof(t_data));
	if (!temp)
		return (discard_chopsticks(data), NULL);
	ft_memcpy(temp, data, sizeof(t_data));
	return (temp);
}

static size_t	init_status(t_data *data, t_philo **status)
{
	t_philo	*temp;
	size_t	i;

	i = 0;
	temp = (t_philo *)malloc((data->total) * sizeof(t_philo));
	if (!temp)
		return (discard_chopsticks(data), KO);
	while (i < data->total)
	{
		temp[i].data_copy = copy_data(data);
		if (temp[i].data_copy == NULL)
			return (reset_status(data, *status, i), KO);
		temp[i].id = i + 1;
		temp[i].last_eaten = 0;
		pthread_mutex_init(&temp[i].eaten_lock, NULL);
		temp[i].times_eaten = 0;
		temp[i].left_chopstick = &data->chopsticks[i];
		temp[i].right_chopstick = \
			&data->chopsticks[(i + 1) % data->total];
		pthread_mutex_init(&temp[i].fatal_lock, NULL);
		temp[i].fatality = false;
		i++;
	}
	*status = temp;
	return (OK);
}

static size_t	init_chopsticks(t_data *data)
{
	size_t	i;

	i = 0;
	data->chopsticks = (pthread_mutex_t *) \
		malloc((data->total) * sizeof(pthread_mutex_t));
	if (!data->chopsticks)
		return (KO);
	while (i < data->total)
	{
		pthread_mutex_init(&data->chopsticks[i], NULL);
		i++;
	}
	return (OK);
}

size_t	init_all(int argc, char **argv, t_data *data, t_philo *status)
{
	data->total = (size_t)ft_atoi(argv[1]);
	data->die_time = (size_t)ft_atoi(argv[2]);
	data->eat_time = (size_t)ft_atoi(argv[3]);
	data->sleep_time = (size_t)ft_atoi(argv[4]);
	if (argc == 6)
		data->full_at = (size_t)ft_atoi(argv[5]);
	else
		data->full_at = 0;
	pthread_mutex_init(&data->print_lock, NULL);
	if (init_chopsticks(data) == KO)
		return (printf("Malloc failure\n"), KO);
	if (gettimeofday(&data->start_time, NULL) != OK)
		return ((printf("TOD failure\n"), KO));
	if (init_status(data, &status) == KO)
		return (printf("Malloc failure\n"), KO);
	if (init_philos(data, status) == KO)
		return (printf("Malloc failure\n"), KO);
	return (OK);
}
