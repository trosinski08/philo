/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_brother_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 20:04:21 by trosinsk          #+#    #+#             */
/*   Updated: 2024/03/18 13:50:14 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	discontinue(t_philo *philos)
{
	sem_wait(*philos->sem_dead);
	if (*philos->dead == 1)
	{
		sem_post(*philos->sem_dead);
		return (1);
	}
	sem_post(*philos->sem_dead);
	return (0);
}

int	non_being(t_philo *philos, int i)
{
	size_t	time_since_meal;
	size_t	current;

	sem_wait(*philos[i].sem_meal);
	current = current_time();
	time_since_meal = current - philos[i].last_meal_time;
	if (time_since_meal >= philos[i].die_time && philos[i].dining == 0)
	{
		sem_post(*philos[i].sem_meal);
		return (1);
	}
	sem_post(*philos[i].sem_meal);
	return (0);
}

int	staying_alive(t_program *program)
{
	t_philo	*philos;
	int		i;
	int		amount;

	i = 0;
	philos = program->philos;
	amount = philos[0].philos_amount;
	while (i < amount)
	{
		if (non_being(philos, i))
		{
			sem_wait(*philos[i].sem_print);
			printf("%zu %d died\n", current_time() - philos[0].start_time, philos[i].id);
			sem_post(*philos[i].sem_print);
			sem_dead(program, i);
			return (1);
		}
		i++;
	}
	return (0);
}

//lines to check if philo is eating
// && !is_eating(philos, i))
int	meal_counter(t_program *program)
{
	t_philo	*philos;
	int		i;
	int		full_philo;
	int		amount;

	i = 0;
	full_philo = 0;
	philos = program->philos;
	amount = philos[0].philos_amount;
	if (philos[0].meals_number == -1)
		return (0);
	while (i < amount)
	{
		sem_wait(*philos[i].sem_meal);
		if (philos[i].meals_eaten >= philos[i].meals_number)
			full_philo++;
		sem_post(*philos[i].sem_meal);
		i++;
	}
	if (full_philo == amount)
	{
		sem_dead(program, 0);
		return (1);
	}
	return (0);
}

void *supervising(void *arg)
{
	t_program *program;
	int philosopher_alive_count;
	int i;
	int status;
	pid_t child_pid_result;

	program = (t_program *)arg;
	philosopher_alive_count = program->philos_amount;

	while (philosopher_alive_count > 0)
	{
		if (program->philos[0].meals_number != -1)
		{
			if (meal_counter(program))
			{
				sem_wait(program->sem_dead);
				if (program->dead_flag == 1) { 
					program->dead_flag = 0;
				}
				sem_post(program->sem_dead);
				break; 
			}
		}

		for (i = 0; i < program->philos_amount; i++)
		{
			if (program->pids[i] > 0) 
			{
				child_pid_result = waitpid(program->pids[i], &status, WNOHANG);
				if (child_pid_result == program->pids[i])
				{
					program->pids[i] = -1; 
					philosopher_alive_count--;

					sem_wait(program->sem_dead);
					if (program->dead_flag == 1) { 
						 program->dead_flag = 0;
					}
					sem_post(program->sem_dead);
					philosopher_alive_count = 0; 
					break; 
				}
				else if (child_pid_result == -1)
				{
					perror("waitpid error in supervising");
					philosopher_alive_count = 0; 
					sem_wait(program->sem_dead);
					program->dead_flag = 0; 
					sem_post(program->sem_dead);
					break; 
				}
			}
		}
		usleep(1000); 
	}
	return (arg);
}
