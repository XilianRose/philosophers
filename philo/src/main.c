/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/03 15:47:20 by mstegema      #+#    #+#                 */
/*   Updated: 2024/01/08 12:40:00 by mstegema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_arguments(int argc, char **argv, t_info *info)
{
	int		i;
	int		j;

	i = 1;
	while (i <= argc)
	{
		j = 0;
		while (argv[i][j] != '\0')
		{
			if (ft_isdigit((int)argv[i][j]) == 0)
				return (KO);
			j++;
		}
		i++;
	}
	info->no_philo = ft_atoi(argv[1]);
	info->die = ft_atoi(argv[2]);
	info->eat = ft_atoi(argv[3]);
	info->sleep = ft_atoi(argv[4]);
	if (argc == 5)
		info->no_eat = ft_atoi(argv[5]);
	else
		info->no_eat = 0;
	return (OK);
}

int	main(int argc, char **argv)
{
	t_info	*info;

	info = NULL;
	if (gettimeofday(time, NULL) != 0)
		return (KO);
	if (argc < 4)
		return (printf("Not enough arguments given\n"), 1);
	else if (argc > 5)
		return (printf("Too many arguments given\n"), 1);
	if (parse_arguments(argc, argv, info) == 0)
		return (printf("Invalid arguments given\n"), 1);
	return (OK);
}
