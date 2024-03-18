/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 21:32:48 by trosinsk          #+#    #+#             */
/*   Updated: 2024/03/18 14:20:59 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_program(t_program *program, t_philo *philos, char **argv)
{
	int		forks_amount;

	forks_amount = ft_atoi(argv[1]);
	program->dead_flag = 1;
	program->philos = philos;
	sem_dead_init(program);
	sem_eating_init(program);
	sem_meal_init(program);
	sem_print_init(program);
	sem_fork_init(program, forks_amount);
}

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
		(&philos[i])->sem_print = &program->sem_print;
		(&philos[i])->sem_dead = &program->sem_dead;
		(&philos[i])->sem_meal = &program->sem_meal;
		(&philos[i])->sem_eating = &program->sem_eating;
		(&philos[i])->dead = &program->dead_flag;
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

// process_creat_error(program); wszystkie procesy exit
void	process_init(t_program *program)
{
	int			i;
	pid_t		pid;

	i = 0;
	pid = fork();
	if (pid < 0)
		exit(1);
	while (i <= program->philos[i].philos_amount)
	{
		if (pid == 0)
		{
			printf("philo no %d create\n", program->philos[i].id);
			while (supervising(program) == 0)
			{
				routine(program->philos);
			}
		}
		else
		{
			fork();
			big_brother_init(program);
			waitpid(pid, NULL, 0);
		}
		i++;
	}
}

void	big_brother_init(t_program *program)
{
	pthread_t	big_brother;

	if (pthread_create(&big_brother, NULL, &supervising, program) != 0)
		thread_creat_error(program);
	if (pthread_join(big_brother, NULL) != 0)
		thread_creat_error(program);
}
