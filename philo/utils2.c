/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 01:12:22 by trosinsk          #+#    #+#             */
/*   Updated: 2024/02/21 04:34:40 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	printing_lock(t_philo *philos, char *str)
{
	size_t	acc_time;

	pthread_mutex_lock(philos->mutex_print);
	acc_time = current_time() - philos->start_time;
	if (!discontinue(philos))
		printf("%zu %d %s\n", acc_time, philos->id, str);
	pthread_mutex_unlock(philos->mutex_print);
}

void	mutex_dead(t_program *program, int i)
{
	t_philo	*philos;

	philos = program->philos;
	pthread_mutex_lock(philos[i].mutex_dead);
	*philos->dead = 0;
	pthread_mutex_unlock(philos[i].mutex_dead);
	return ;
}

void	handle_1(t_philo *philos)
{
	ft_usleep(philos->die_time);
	pthread_mutex_unlock(philos->right_f);
	return ;
}

// int	is_eating(t_philo *philos, int i)
// {
// 	int	j;

// 	j = 0;
// 	// pthread_mutex_lock(philos[i].mutex_eating);
// 	if (philos[i].dining == 0)
// 		j = 0;
// 	else
// 		j = 1;
// 	// pthread_mutex_unlock(philos[i].mutex_eating);
// 	return (j);
// }
