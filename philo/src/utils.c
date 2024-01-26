/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/03 16:14:02 by mstegema      #+#    #+#                 */
/*   Updated: 2024/01/26 12:33:28 by mstegema      ########   odam.nl         */
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

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*d;
	char	*s;

	i = 0;
	d = (char *)dst;
	s = (char *)src;
	if (dst == 0 && src == 0)
		return ((void *)dst);
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return ((void *)dst);
}

size_t	get_time(t_data *data)
{
	struct timeval	*current;
	size_t			ms;

	current = NULL;
	if (gettimeofday(current, NULL) != OK)
		return (0);
	ms = (current->tv_sec - data->start_time->tv_sec) * 1000000 + \
		(current->tv_usec - data->start_time->tv_usec) / 1000;
	return (ms);
}

void	print_message(t_data *data, size_t timestamp, size_t id, char *message)
{
	pthread_mutex_lock(&data->print_lock);
	printf("%zu %zu %s ", timestamp, id, message);
	pthread_mutex_unlock(&data->print_lock);
}
