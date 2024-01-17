/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/17 14:15:36 by mstegema      #+#    #+#                 */
/*   Updated: 2024/01/17 16:21:12 by mstegema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static size_t	init_philos(t_data *data)
{
	size_t	i;
	t_philo	philo;

	i = 0;
	data->philos = (t_philo *)malloc((data->nb_philos + 1) * sizeof(t_philo));
	if (!data->philos)
		return (discard_chopsticks(data), KO);
	while (i < data->nb_philos)
	{
		philo = data->philos[i];
		philo.nb = i + 1;
		philo.last_eaten = 0;
		philo.times_eaten = 0;
		philo.left_chopstick = &data->chopsticks[i];
		philo.right_chopstick = &data->chopsticks[(i + 1) % data->nb_philos];
		pthread_create(&philo.thread, NULL, &routine, (void *)data);
		i++;
	}

}

static size_t	init_chopsticks(t_data *data)
{
	size_t	i;

	i = 0;
	data->chopsticks = (pthread_mutex_t *) \
		malloc((data->nb_philos + 1) * sizeof(pthread_mutex_t));
	if (!data->chopsticks)
		return (KO);
	while (i < data->nb_philos)
	{
		pthread_mutex_init(&data->chopsticks[i], NULL);
		i++;
	}
	return (OK);
}

size_t	init_data(int argc, char **argv, t_data *data)
{
	data->nb_philos = ft_atoi(argv[1]);
	data->die_time = ft_atoi(argv[2]);
	data->eat_time = ft_atoi(argv[3]);
	data->sleep_time = ft_atoi(argv[4]);
	if (argc == 5)
		data->nb_eat = ft_atoi(argv[5]);
	else
		data->nb_eat = 0;
	if (init_chopsticks == KO)
		return (KO);
	if (init_philos == KO)
		return (KO);
	return (OK);
}
