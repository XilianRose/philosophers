/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/03 15:09:45 by mstegema      #+#    #+#                 */
/*   Updated: 2024/01/17 16:16:57 by mstegema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>

# define OK 0
# define KO 1

typedef struct s_philo
{
	size_t			nb;
	pthread_t		thread;
	size_t			last_eaten;
	size_t			times_eaten;
	pthread_mutex_t	*left_chopstick;
	pthread_mutex_t	*right_chopstick;
}	t_philo;

typedef struct s_data
{
	size_t			nb_philos;
	size_t			die_time;
	size_t			eat_time;
	size_t			sleep_time;
	size_t			nb_eat;
	struct timeval	*start_time;
	t_philo			*philos;
	pthread_mutex_t	*chopsticks;
	pthread_mutex_t	*print_lock;
}	t_data;

// parsing
int		parsing(int argc, char **argv, t_data *data);

// initalization
size_t	init_data(int argc, char **argv, t_data *data);

// routine
void	routine(void);

//	utils
int		ft_atoi(const char *str);
size_t	get_time(t_data *data);
void	discard_chopsticks(t_data *data);

#endif
