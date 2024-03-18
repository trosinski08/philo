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

void	sleeping(t_philo *philos)
{
	printing_lock(philos, S);
	ft_usleep(philos->sleep_time);
	printing_lock(philos, T);
}

void	dining(t_philo *philos)
{
	sem_wait(*philos->fork);
	printing_lock(philos, F);
	if (philos->philos_amount == 1)
		handle_1(philos);
	sem_wait(*philos->fork);
	printing_lock(philos, F);
	philos->dining = 1;
	printing_lock(philos, E);
	sem_wait(*philos->sem_meal);
	philos->last_meal_time = current_time();
	philos->meals_eaten++;
	sem_post(*philos->sem_meal);
	ft_usleep(philos->eat_time);
	philos->dining = 0;
	sem_post(*philos->fork);
	if (philos->philos_amount != 1)
		sem_post(*philos->fork);
}

void	*routine(t_philo *philos)
{
	if (philos->id % 2 == 0)
		ft_usleep(100);
	while (!discontinue(philos))
	{
		dining(philos);
		sleeping(philos);
	}
	return (0);
}
