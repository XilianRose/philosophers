/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/03 15:09:45 by mstegema      #+#    #+#                 */
/*   Updated: 2024/01/18 18:03:13 by mstegema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdbool.h>

# define OK 0
# define KO 1

typedef struct s_philo
{
	size_t			nb;
	size_t			last_eaten;
	size_t			times_eaten;
	pthread_mutex_t	*left_chopstick;
	pthread_mutex_t	*right_chopstick;
	// bool			died;
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	size_t			nb_philos;
	size_t			die_time;
	size_t			eat_time;
	size_t			sleep_time;
	size_t			nb_eat;
	pthread_mutex_t	*print_lock;
	pthread_mutex_t	*chopsticks;
	struct timeval	*start_time;
	pthread_t		*philos;
}	t_data;

// parsing
int		parsing(int argc, char **argv);

// initalization
size_t	init_data(int argc, char **argv, t_data *data, pthread_t *philos);

// routine
void	routine(void *data);

//	utils
int		ft_atoi(const char *str);
size_t	get_time(t_data *data);
void	discard_chopsticks(t_data *data);
void	clean_exit(t_data *data, t_philo *status);
void	print_message(t_data *data, size_t timestamp, size_t nb, char *message);

#endif
