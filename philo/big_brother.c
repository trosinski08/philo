/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_brother.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 20:04:21 by trosinsk          #+#    #+#             */
/*   Updated: 2024/02/21 04:33:59 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	discontinue(t_philo *philos)
{
	pthread_mutex_lock(philos->mutex_dead);
	if (*philos->dead == 1)
	{
		pthread_mutex_unlock(philos->mutex_dead);
		return (0);
	}
	pthread_mutex_unlock(philos->mutex_dead);
	return (1);
}

int	non_being(t_philo *philos, int i)
{
	pthread_mutex_lock(philos[i].mutex_meal);
	if (philos[i].die_time <= current_time() - philos[i].last_meal_time)
		// && philos[i].dining == 0)
	{
		pthread_mutex_unlock(philos[i].mutex_meal);
		return (1);
	}
	pthread_mutex_unlock(philos[i].mutex_meal);
	return (0);
}

int	staying_alive(t_program *program)
{
	t_philo	*philos;
	int		i;

	i = 0;
	philos = program->philos;
	while (i <= philos[i].philos_amount)
	{
		if (non_being(philos, i))
		{
			printing_lock(philos, D);
			mutex_dead(program, i);
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
	while (i < philos[i].philos_amount)
	{
		pthread_mutex_lock(philos[i].mutex_meal);
		if (philos[i].meals_eaten >= philos[i].meals_number)
			// && !is_eating(philos, i))
			full_philo++;
		pthread_mutex_unlock(philos[i].mutex_meal);
		i++;
	}
	if (full_philo == philos[0].philos_amount)
	{
		mutex_dead(program, 0);
		return (1);
	}
	return (0);
}

void	*supervising(void *arg)
{
	t_program	*program;

	program = (t_program *)arg;
	while (1)
	{
		if (staying_alive(program) || meal_counter(program))
			break ;
	}
	return (arg);
}
