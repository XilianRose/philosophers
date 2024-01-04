/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   actions.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/04 15:42:34 by mstegema      #+#    #+#                 */
/*   Updated: 2024/01/04 18:04:39 by mstegema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_info *info)
{
	usleep(info->eat);
}

void	sleep(t_info *info)
{
	printf("%i X is sleeping", info->time->tv_usec);
	usleep(info->sleep);
}

void	think(t_info *info)
{


}
