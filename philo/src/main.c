/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/03 15:47:20 by mstegema      #+#    #+#                 */
/*   Updated: 2024/02/01 15:09:06 by mstegema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	everyone_full(t_data *data, t_philo *status)
{
	size_t	i;

	i = 0;
	while (i < data->total)
	{
		pthread_mutex_lock(&status[i].eaten_lock);
		if (status[i].times_eaten < data->full_at)
			return (pthread_mutex_unlock(&status[i].eaten_lock), false);
		pthread_mutex_unlock(&status[i].eaten_lock);
		i++;
	}
	return (true);
}

static void	welfare_check(t_data *data, t_philo *status)
{
	size_t	i;

	i = 0;
	while (1)
	{
		if (i == data->total)
			i = 0;
		pthread_mutex_lock(&status[i].fatal_lock);
		if (status[i].fatality == true || \
		(data->full_at > 0 && everyone_full(data, status) == true))
		{
			pthread_mutex_unlock(&status[i].fatal_lock);
			i = 0;
			while (i < data->total)
			{
				pthread_mutex_lock(&status[i].fatal_lock);
				status[i].fatality = true;
				pthread_mutex_unlock(&status[i].fatal_lock);
				i++;
			}
			return ;
		}
		pthread_mutex_unlock(&status[i].fatal_lock);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data		data;
	t_philo		*status;

	status = NULL;
	if (argc < 5 || argc > 6)
		return (printf("Invalid number of arguments given\n"), KO);
	if (parsing(argc, argv) == KO)
		return (printf("Invalid arguments given\n"), KO);
	status = init_all(argc, argv, &data, status);
	if (status == NULL)
		return (KO);
	welfare_check(&data, status);
	clean_exit(&data, status);
	return (OK);
}
