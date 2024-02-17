/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 19:22:05 by trosinsk          #+#    #+#             */
/*   Updated: 2024/02/17 20:49:11 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	(void)arg;

	// eat
	//sleep
	//think

	printf("Philosopher do routine!\n");
	return (0);
}

// void	thread_init(t_program *program, t_philo *philos)
void	thread_init(t_program *program)

{
	pthread_t	big_brother;
	int			i;

	i = 1;
	if (pthread_create(&big_brother, NULL, &monitoring, program) != 0)
	{
		printf("Thread creation error");
		exit(1);
	}
	while (i <= program->philos[i].number_of_philos)
	{
		if (pthread_create(&program->philos[i].thread, NULL, &routine, program)
			!= 0)
		{
			printf("Thread creation error");
			exit(1);
		}
		i++;
	}
	while (i <= program->philos[i].number_of_philos)
	{
		if (pthread_join(program->philos[i].thread, NULL)
			!= 0)
		{
			printf("Thread creation error");
			exit(1);
		}
		i++;
	}
}
