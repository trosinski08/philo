/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 19:22:05 by trosinsk          #+#    #+#             */
/*   Updated: 2024/02/21 04:34:23 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleeping(t_philo *philos)
{
	printing_lock(philos, S);
	ft_usleep(philos->sleep_time);
	printing_lock(philos, T);
}

void	dining(t_philo *philos)
{
	pthread_mutex_lock(philos->right_f);
	printing_lock(philos, F);
	if (philos->philos_amount == 1)
		handle_1(philos);
	pthread_mutex_lock(philos->left_f);
	printing_lock(philos, F);
	philos->dining = 1;
	printing_lock(philos, E);
	pthread_mutex_lock(philos->mutex_meal);
	philos->last_meal_time = current_time();
	philos->meals_eaten++;
	pthread_mutex_unlock(philos->mutex_meal);
	ft_usleep(philos->eat_time);
	philos->dining = 0;
	pthread_mutex_unlock(philos->left_f);
	if (philos->philos_amount != 1)
		pthread_mutex_unlock(philos->right_f);
}

void	*routine(void *arg)
{
	t_philo	*philos;

	philos = (t_philo *)arg;
	if (philos->id % 2 == 0)
		ft_usleep(100);
	while (!discontinue(philos))
	{
		dining(philos);
		sleeping(philos);
	}
	return (0);
}
