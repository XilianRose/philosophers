/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/17 14:15:36 by mstegema      #+#    #+#                 */
/*   Updated: 2024/01/18 17:37:10 by mstegema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static size_t	init_philos(t_data *data, t_philo *status)
{
	size_t	i;

	i = 0;
	data->philos = (pthread_t *)malloc((data->nb_philos) * sizeof(pthread_t));
	if (!data->philos)
		return (discard_chopsticks(data), KO);
	status = (t_philo *)malloc((data->nb_philos) * sizeof(t_philo));
	if (!status)
		return (discard_chopsticks(data), free(data->philos), KO);
	while (i < data->nb_philos)
	{
		status[i].nb = i + 1;
		status[i].last_eaten = 0;
		status[i].times_eaten = 0;
		status[i].left_chopstick = &data->chopsticks[i];
		status[i].right_chopstick = \
			&data->chopsticks[(i + 1) % data->nb_philos];
		// status[i].died = false;
		status[i].data = data;
		pthread_create(&data->philos[i], NULL, &routine, (void *)&status[i]);
		i++;
	}

}

static size_t	init_chopsticks(t_data *data)
{
	size_t	i;

	i = 0;
	data->chopsticks = (pthread_mutex_t *) \
		malloc((data->nb_philos) * sizeof(pthread_mutex_t));
	if (!data->chopsticks)
		return (KO);
	while (i < data->nb_philos)
	{
		pthread_mutex_init(&data->chopsticks[i], NULL);
		i++;
	}
	return (OK);
}

size_t	init_data(int argc, char **argv, t_data *data, pthread_t *philos)
{
	t_philo	*status;

	data->nb_philos = ft_atoi(argv[1]);
	data->die_time = ft_atoi(argv[2]);
	data->eat_time = ft_atoi(argv[3]);
	data->sleep_time = ft_atoi(argv[4]);
	if (argc == 5)
		data->nb_eat = ft_atoi(argv[5]);
	else
		data->nb_eat = 0;
	pthread_mutex_init(&data->print_lock, NULL);
	if (init_chopsticks(data) == KO)
		return (printf("Malloc failure\n"), KO);
	if (gettimeofday(data->start_time, NULL) != OK)
		return ((printf("TOD failure\n"), KO));
	if (init_philos(data, status) == KO)
		return (printf("Malloc failure\n"), KO);
	return (OK);
}
