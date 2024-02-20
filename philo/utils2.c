/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 01:12:22 by trosinsk          #+#    #+#             */
/*   Updated: 2024/02/20 01:21:31 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	handle_1(t_philo *philos)
{
	ft_usleep(philos->time_to_die);
	pthread_mutex_unlock(philos->r_fork);
	return ;
}

void	dead_lock(t_philo *philos, int i)
{
	pthread_mutex_lock(philos[i].dead_lock);
	*philos->dead = 1;
	pthread_mutex_unlock(philos[i].dead_lock);
}

void	arg_number_error(void)
{
	printf("Error: wrong number of arguments\n");
	exit(1);
}

void	number_of_philos_error(void)
{
	printf("Error: wrong number of philosophers\n");
	exit(1);
}

void	argv_validator(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < 48 || argv[i][j] > 57)
				printf("wrong imput format, use only numbers\n");
			j++;
		}
		i++;
	}
}
