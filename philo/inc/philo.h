/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/03 15:09:45 by mstegema      #+#    #+#                 */
/*   Updated: 2024/01/04 10:02:52 by mstegema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>

typedef struct s_info
{
	size_t	no_philo;
	size_t	die;
	size_t	eat;
	size_t	sleep;
	size_t	no_eat;
}	t_info;

//	utils
int	ft_atoi(const char *str);
int	ft_isdigit(int c);

#endif
