/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/03 16:14:02 by mstegema      #+#    #+#                 */
/*   Updated: 2024/01/04 16:48:20 by mstegema      ########   odam.nl         */
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

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}
