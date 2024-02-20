/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 19:22:05 by trosinsk          #+#    #+#             */
/*   Updated: 2024/02/20 01:30:38 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thinking(t_philo *philos)
{
	printing_lock(philos, T);
}

void	sleeping(t_philo *philos)
{
	printing_lock(philos, S);
	ft_usleep(philos->time_to_sleep);
}

void	eating(t_philo *philos)
{
	pthread_mutex_lock(philos->r_fork);
	printing_lock(philos, F);
	if (philos->number_of_philos == 1)
		handle_1(philos);
	pthread_mutex_lock(philos->l_fork);
	printing_lock(philos, F);
	philos->eating = 1;
	printing_lock(philos, E);
	pthread_mutex_lock(philos->meal_lock);
	philos->last_meal = current_time();
	philos->meals_eaten++;
	pthread_mutex_unlock(philos->meal_lock);
	ft_usleep(philos->time_to_eat);
	philos->eating = 0;
	pthread_mutex_unlock(philos->l_fork);
	pthread_mutex_unlock(philos->r_fork);
}

void	*routine(void *arg)
{
	t_philo	*philos;

	philos = (t_philo *)arg;
	if (philos->id % 2 == 0)
		ft_usleep(philos->time_to_eat - 10);
	while (!discontinue(philos))
	{
		eating(philos);
		sleeping(philos);
		thinking(philos);
	}
	return (0);
}
