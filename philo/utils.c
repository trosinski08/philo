/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 19:17:57 by trosinsk          #+#    #+#             */
/*   Updated: 2024/02/19 23:28:08 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *num)
{
	int	i;
	int	sign;
	int	conv_value;

	i = 0;
	sign = 1;
	conv_value = 0;
	while ((num[i] >= 9 && num[i] <= 13) || num[i] == 32)
		i++;
	if (num[i] == '-' || num[i] == '+')
	{
		if (num[i] == '-')
			sign = -sign;
		i++;
	}
	while (num[i] >= '0' && num[i] <= '9')
	{
		conv_value = (num[i] - '0') + (conv_value * 10);
		i++;
	}
	return (conv_value * sign);
}

size_t	current_time(void)
{
	struct timeval	tv;
	size_t			time_in_sec;
	size_t			time_in_usec;

	gettimeofday(&tv, NULL);
	time_in_sec = tv.tv_sec;
	time_in_usec = tv.tv_usec;
	return (time_in_sec * 1000 + time_in_usec / 1000);
}

size_t	ft_usleep(size_t time)
{
	size_t	start;

	start = current_time();
	while ((current_time() - start) < time)
		usleep(500);
	return (0);
}

void	mutex_destructor(t_program *program)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&program->write_lock);
	pthread_mutex_destroy(&program->dead_lock);
	pthread_mutex_destroy(&program->meal_lock);
	while (i <= program->philos[i].number_of_philos)
	{
		pthread_mutex_destroy(&program->fork[i]);
		i++;
	}
}

void	printing_lock(t_philo *philos, char *str)
{
	size_t	acc_time;

	pthread_mutex_lock(philos->write_lock);
	acc_time = current_time() - philos->start_time;
	if (!discontinue(philos))
		printf("%zu %d %s\n", acc_time, philos->id, str);
	pthread_mutex_unlock(philos->write_lock);
}
