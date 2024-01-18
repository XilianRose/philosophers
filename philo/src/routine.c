/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/04 15:42:34 by mstegema      #+#    #+#                 */
/*   Updated: 2024/01/18 17:53:50 by mstegema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	think(t_philo *status)
{
	
}

void	sleep(t_philo *status)
{
	if (get_time(status->data) - status->last_eaten >= status->data->die_time)
	
}

void	eat(t_philo *status)
{
	if (get_time(status->data) - status->last_eaten >= status->data->die_time)
	
}

void	routine(void *arg)
{
	t_philo	*status;

	status = (t_philo *)arg;

	return ;
}
