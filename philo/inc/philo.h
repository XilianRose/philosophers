/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/03 15:09:45 by mstegema      #+#    #+#                 */
/*   Updated: 2024/01/08 12:39:23 by mstegema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>

# define OK 0;
# define KO 1;

typedef struct s_info
{
	size_t			no_philo;
	size_t			die;
	size_t			eat;
	size_t			sleep;
	size_t			no_eat;
	struct timeval	*time;
	pthread_t		*philos;
	pthread_mutex_t	*chopsticks;
}	t_info;

//	utils
size_t	get_time(t_info *info);
int		ft_atoi(const char *str);
int		ft_isdigit(int c);

#endif
