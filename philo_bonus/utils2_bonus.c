/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:48:12 by trosinsk          #+#    #+#             */
/*   Updated: 2024/03/18 14:31:07 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	printing_lock(t_philo *philos, char *str)
{
	size_t	acc_time;

	sem_wait(*philos->sem_print);
	acc_time = current_time() - philos->start_time;
	printf("%zu %d %s\n", acc_time, philos->id, str);
	fflush(stdout);
	sem_post(*philos->sem_print);
}

void	sem_dead(t_program *program, int i)
{
	t_philo	*philos;

	philos = program->philos;
	sem_wait(*philos[i].sem_dead);
	*philos->dead = 0;
	sem_post(*philos[i].sem_dead);
	return ;
}

void	handle_1(t_philo *philos)
{
	ft_usleep(philos->die_time);
	sem_post(*philos->fork);

	sem_wait(*philos->sem_print);
	printf("%zu %d died\n", current_time() - philos->start_time, philos->id);
	fflush(stdout);
	sem_post(*philos->sem_print);

	sem_wait(*philos->sem_dead);
	*philos->dead = 0;
	sem_post(*philos->sem_dead);
	exit(0);
}

int	is_eating(t_philo *philos, int i)
{
	int	j;

	j = 0;
	sem_wait(*philos[i].sem_eating);
	if (philos[i].dining == 0)
		j = 0;
	else
		j = 1;
	sem_post(*philos[i].sem_eating);
	return (j);
}
