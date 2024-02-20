/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 16:54:36 by trosinsk          #+#    #+#             */
/*   Updated: 2024/02/20 01:28:58 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_data(char **argv, t_philo *philos)
{
	philos->number_of_philos = ft_atoi(argv[1]);
	philos->time_to_die = ft_atoi(argv[2]);
	philos->time_to_eat = ft_atoi(argv[3]);
	philos->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		philos->meals_number = ft_atoi(argv[5]);
	else
		philos->meals_number = -1;
}

void	init_program(t_program *program, t_philo *philos, char **argv)
{
	int	i;

	i = 0;
	program->dead_flag = 1;
	program->philos = philos;
	pthread_mutex_init(&program->write_lock, NULL);
	pthread_mutex_init(&program->dead_lock, NULL);
	pthread_mutex_init(&program->meal_lock, NULL);
	while (i <= ft_atoi(argv[1]))
	{
		pthread_mutex_init(&program->fork[i], NULL);
		i++;
	}
}

void	philos_init(t_philo *philos, t_program *program, char **argv)
{
	int	i;

	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		(&philos[i])->id = i + 1;
		(&philos[i])->eating = 0;
		(&philos[i])->meals_eaten = 0;
		init_data(argv, &philos[i]);
		(&philos[i])->start_time = current_time();
		(&philos[i])->last_meal = current_time();
		philos[i].write_lock = &program->write_lock;
		philos[i].dead_lock = &program->dead_lock;
		philos[i].meal_lock = &program->meal_lock;
		philos[i].dead = &program->dead_flag;
		philos[i].r_fork = &program->fork[i];
		if (i == 0)
			philos[i].l_fork = &program->fork[philos[i].number_of_philos - 1];
		else
			philos[i].l_fork = &program->fork[i - 1];
		i++;
	}
}

void	thread_init(t_program *program)
{
	pthread_t	big_brother;
	int			i;

	i = 0;
	if (pthread_create(&big_brother, NULL, &monitoring, program) != 0)
		thread_creat_error(program);
	while (i <= program->philos[i].number_of_philos)
	{
		if (pthread_create(&program->philos[i].thread, NULL, &routine,
				&program->philos[i]) != 0)
			thread_creat_error(program);
		i++;
	}
	if (pthread_join(big_brother, NULL) != 0)
		thread_creat_error(program);
	i = 0;
	while (i <= program->philos[i].number_of_philos)
	{
		if (pthread_join(program->philos[i].thread, NULL)
			!= 0)
			thread_creat_error(program);
		i++;
	}
}
