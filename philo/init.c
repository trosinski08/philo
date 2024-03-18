/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 16:54:36 by trosinsk          #+#    #+#             */
/*   Updated: 2024/03/17 23:19:05 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_program(t_program *program, t_philo *philos, char **argv)
{
	int	i;

	i = 0;
	program->dead_flag = 1;
	program->philos = philos;
	if (pthread_mutex_init(&program->mutex_print, NULL) != 0)
		mutex_creat_error(program, "write");
	if (pthread_mutex_init(&program->mutex_dead, NULL) != 0)
		mutex_creat_error(program, "dead");
	if (pthread_mutex_init(&program->mutex_meal, NULL) != 0)
		mutex_creat_error(program, "program");
	if (pthread_mutex_init(&program->mutex_eating, NULL) != 0)
		mutex_creat_error(program, "eating");
	while (i < ft_atoi(argv[1]))
	{
		if (pthread_mutex_init(&program->fork[i], NULL) != 0)
			mutex_creat_error(program, "fork");
		i++;
	}
}
		//lines to check adresses of forks
		// printf("philos[%d].id = right fork%p 
		//left fork%p\n", i, philos[i].right_f, philos[i].left_f);

void	philos_init(t_philo *philos, t_program *program, char **argv)
{
	int	i;

	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		(&philos[i])->id = i + 1;
		(&philos[i])->dining = 0;
		(&philos[i])->meals_eaten = 0;
		init_data(argv, &philos[i]);
		(&philos[i])->start_time = current_time();
		(&philos[i])->last_meal_time = current_time();
		(&philos[i])->mutex_print = &program->mutex_print;
		(&philos[i])->mutex_dead = &program->mutex_dead;
		(&philos[i])->mutex_meal = &program->mutex_meal;
		(&philos[i])->mutex_eating = &program->mutex_eating;
		(&philos[i])->dead = &program->dead_flag;
		(&philos[i])->left_f = &program->fork[(i)];
		(&philos[i])->right_f = &program->fork[(i + 1) % ft_atoi(argv[1])];
		i++;
	}
}

void	init_data(char **argv, t_philo *philos)
{
	philos->philos_amount = ft_atoi(argv[1]);
	philos->die_time = ft_atoi(argv[2]);
	philos->eat_time = ft_atoi(argv[3]);
	philos->sleep_time = ft_atoi(argv[4]);
	if (argv[5])
		philos->meals_number = ft_atoi(argv[5]);
	else
		philos->meals_number = -1;
}

void	thread_init(t_program *program)
{
	pthread_t	big_brother;
	int			i;

	i = 0;
	if (pthread_create(&big_brother, NULL, &supervising, program) != 0)
		thread_creat_error(program);
	while (i <= program->philos[i].philos_amount)
	{
		if (pthread_create(&program->philos[i].thread, NULL, &routine,
				&program->philos[i]) != 0)
			thread_creat_error(program);
		i++;
	}
	if (pthread_join(big_brother, NULL) != 0)
		thread_creat_error(program);
	i = 0;
	while (i <= program->philos[i].philos_amount)
	{
		if (pthread_join(program->philos[i].thread, NULL) != 0)
			thread_creat_error(program);
		i++;
	}
}
