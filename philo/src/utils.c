/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/03 16:14:02 by mstegema      #+#    #+#                 */
/*   Updated: 2024/01/17 15:41:23 by mstegema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	multiplier;
	int	num;

	i = 0;
	multiplier = 1;
	num = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || \
		str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			multiplier = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return (multiplier * num);
}

size_t	get_time(t_data *data)
{
	struct timeval	*current;
	size_t			ms;

	if (gettimeofday(current, NULL) != 0)
		return (0);
	ms = (current->tv_sec - data->start_time->tv_sec) * 1000000 + \
		(current->tv_usec - data->start_time->tv_usec) / 1000;
	return (ms);
}

void	discard_chopsticks(t_data *data)
{
	size_t	i;

	i = 0;
	if (!data->chopsticks)
		return ;
	while (i < data->nb_philos)
	{
		pthread_mutex_destroy(&data->chopsticks[i]);
		i++;
	}
	free(data->chopsticks);
	data->chopsticks = NULL;
}

void	clean_exit(t_data *data)
{
	discard_chopsticks(data);
}
