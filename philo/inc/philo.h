/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/03 15:09:45 by mstegema      #+#    #+#                 */
/*   Updated: 2024/02/01 11:22:53 by mstegema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdbool.h>

# define OK 0
# define KO 1

typedef enum e_action
{
	EATING,
	SLEEPING
}	t_action;

typedef struct s_data
{
	size_t			total;
	size_t			die_time;
	size_t			eat_time;
	size_t			sleep_time;
	size_t			full_at;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	*chopsticks;
	struct timeval	start_time;
	pthread_t		*philos;
}	t_data;

typedef struct s_philo
{
	t_data			*data_copy;
	size_t			id;
	size_t			last_eaten;
	pthread_mutex_t	eaten_lock;
	size_t			times_eaten;
	pthread_mutex_t	*left_chopstick;
	pthread_mutex_t	*right_chopstick;
	pthread_mutex_t	fatal_lock;
	bool			fatality;
}	t_philo;

// parsing
int		parsing(int argc, char **argv);

// initalization
t_philo	*init_all(int argc, char **argv, t_data *data, t_philo *status);

// routine
void	*routine(void *data);

// free
void	reset_status(t_philo *status, size_t max);
void	discard_chopsticks(t_data *data);
void	clean_exit(t_data *data, t_philo *status);

//	utils
int		ft_atoi(const char *str);
void	*ft_memcpy(void *dst, const void *src, size_t n);
size_t	get_time(t_data *data);
void	print_message(t_data *data, size_t timestamp, size_t nb, char *message);

#endif
