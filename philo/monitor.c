/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 20:04:21 by trosinsk          #+#    #+#             */
/*   Updated: 2024/02/20 01:17:53 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	discontinue(t_philo *philos)
{
	pthread_mutex_lock(philos->dead_lock);
	if (*philos->dead == 1)
	{
		pthread_mutex_unlock(philos->dead_lock);
		return (0);
	}
	pthread_mutex_unlock(philos->dead_lock);
	return (1);
}

int	non_being(t_philo *philos, int i)
{
	pthread_mutex_lock(philos[i].meal_lock);
	if (philos[i].time_to_die <= current_time() - philos[i].last_meal
		&& philos[i].eating == 0)
	{
		pthread_mutex_unlock(philos[i].meal_lock);
		return (1);
	}
	pthread_mutex_unlock(philos[i].meal_lock);
	return (0);
}

int	staying_alive(t_program *program)
{
	t_philo	*philos;
	int		i;

	i = 0;
	philos = program->philos;
	while (i <= philos[i].number_of_philos)
	{
		if (non_being(philos, i))
		{
			printing_lock(philos, D);
			dead_lock(philos, i);
			return (1);
		}
		i++;
	}
	return (0);
}

int	meal_counter(t_program *program)
{
	t_philo	*philos;
	int		i;
	int		full_philo;

	i = 0;
	full_philo = 0;
	philos = program->philos;
	if (philos[i].meals_number == -1)
		return (0);
	while (i < philos[i].number_of_philos)
	{
		pthread_mutex_lock(philos[i].meal_lock);
		if (philos[i].meals_eaten >= philos[i].meals_number)
			full_philo++;
		pthread_mutex_unlock(philos[i].meal_lock);
		i++;
	}
	if (full_philo == philos[0].number_of_philos)
	{
		dead_lock(philos, 0);
		return (1);
	}
	return (0);
}

void	*monitoring(void *arg)
{
	t_program	*prog;

	prog = (t_program *)arg;
	while (1)
	{
		if (staying_alive(prog) || meal_counter(prog))
			break ;
	}
	return (arg);
}
