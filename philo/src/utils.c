/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/03 16:14:02 by mstegema      #+#    #+#                 */
/*   Updated: 2024/01/11 14:42:26 by mstegema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_time(t_info *info)
{
	struct timeval	*current;
	size_t			ms;

	if (gettimeofday(current, NULL) != 0)
		return (0);
	ms = (current->tv_sec - info->time->tv_sec) * 1000000 + \
		(current->tv_usec - info->time->tv_usec) / 1000;
	return (ms);
}
