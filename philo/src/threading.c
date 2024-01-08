/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threading.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/04 15:41:45 by mstegema      #+#    #+#                 */
/*   Updated: 2024/01/08 15:13:59 by mstegema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	init_philos(t_info *info)
{

}

size_t	init_chopsticks(t_info *info)
{
	size_t	i;

	i = 0;
	info->chopsticks = (pthread_mutex_t *) \
		malloc((info->no_philo + 1) * sizeof(pthread_mutex_t));
	if (!info->chopsticks)
	{
		free(info->philos);
		info->philos = NULL;
		return (KO);
	}
	while(i < info->no_philo)
	{
		pthread_mutex_init(&info->chopsticks[i], NULL);
		i++;
	}
	return (OK);
}

size_t	init_data(t_info *info)
{
	info->philos = (pthread_t *) \
		malloc((info->no_philo + 1) * sizeof(pthread_t));
	if (!info->philos)
		return (KO);
	return (OK);
}
