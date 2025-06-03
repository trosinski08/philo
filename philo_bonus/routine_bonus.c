/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 14:00:58 by trosinsk          #+#    #+#             */
/*   Updated: 2024/03/18 14:30:16 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	check_death(t_philo *philos)
{
	size_t	time_since_meal;
	size_t	current;

	sem_wait(*philos->sem_meal);
	current = current_time();
	time_since_meal = current - philos->last_meal_time;
	
	if (time_since_meal >= philos->die_time)
	{
		sem_wait(*philos->sem_print);
		sem_wait(*philos->sem_dead);
		printf("%zu %d died\n", current - philos->start_time, philos->id);
		fflush(stdout);
		*philos->dead = 0;
		sem_post(*philos->sem_dead);
		sem_post(*philos->sem_print);
		sem_post(*philos->sem_meal);
		exit(0);
	}
	sem_post(*philos->sem_meal);
}

void	sleeping(t_philo *philos)
{
	printing_lock(philos, S);
	ft_usleep(philos->sleep_time);
	printing_lock(philos, T);
}

void	dining(t_philo *philos)
{
	if (philos->philos_amount == 1)
	{
		sem_wait(*philos->fork);
		printing_lock(philos, F);
		handle_1(philos);
		return;
	}

	sem_wait(*philos->fork);
	sem_wait(*philos->fork);
	
	sem_wait(*philos->sem_eating);
	philos->dining = 1;
	printing_lock(philos, F);
	printing_lock(philos, F);
	sem_post(*philos->sem_eating);

	sem_wait(*philos->sem_meal);
	philos->last_meal_time = current_time();
	philos->meals_eaten++;
	sem_post(*philos->sem_meal);

	printing_lock(philos, E);
	ft_usleep(philos->eat_time);

	sem_wait(*philos->sem_eating);
	philos->dining = 0;
	sem_post(*philos->sem_eating);

	sem_post(*philos->fork);
	sem_post(*philos->fork);
}

void	*routine(t_philo *philos)
{
	if (philos->id % 2 == 0)
		ft_usleep(10);

	printing_lock(philos, T);

	while (discontinue(philos))
	{
		dining(philos);

		if (philos->meals_number != -1 && philos->meals_eaten >= philos->meals_number)
		{
			sem_wait(*philos->sem_dead);
			if (*philos->dead == 1)
				*philos->dead = 0;
			sem_post(*philos->sem_dead);
			return (0);
		}

		check_death(philos);

		if (!discontinue(philos))
			break;

		sleeping(philos);

		check_death(philos);

		if (!discontinue(philos))
			break;
	}
	return (0);
}
