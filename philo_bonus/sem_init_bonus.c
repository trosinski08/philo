/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_init_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 22:52:00 by trosinsk          #+#    #+#             */
/*   Updated: 2024/03/18 14:23:27 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	sem_dead_init(t_program *program)
{
	const char	*dead;
	sem_t		*sem_dead;

	dead = "sem_dead";
	sem_unlink(dead);
	sem_dead = sem_open(dead, O_CREAT | O_EXCL, 0666, 1);
	if (sem_dead == SEM_FAILED)
		sem_creat_error("dead");
	program->sem_dead = sem_dead;
}

void	sem_eating_init(t_program *program)
{
	const char	*eating;
	sem_t		*sem_eating;

	eating = "sem_eating";
	sem_unlink(eating);
	sem_eating = sem_open(eating, O_CREAT | O_EXCL, 0666, 1);
	if (sem_eating == SEM_FAILED)
		sem_creat_error("eating");
	program->sem_eating = sem_eating;
}

void	sem_meal_init(t_program *program)
{
	const char	*meal;
	sem_t		*sem_meal;

	meal = "sem_meal";
	sem_unlink(meal);
	sem_meal = sem_open(meal, O_CREAT | O_EXCL, 0666, 1);
	if (sem_meal == SEM_FAILED)
		sem_creat_error("meal");
	program->sem_meal = sem_meal;
}

void	sem_print_init(t_program *program)
{
	const char	*print;
	sem_t		*sem_print;

	print = "sem_print";
	sem_unlink(print);
	sem_print = sem_open(print, O_CREAT | O_EXCL, 0666, 1);
	if (sem_print == SEM_FAILED)
		sem_creat_error("print");
	program->sem_print = sem_print;
}

void	sem_fork_init(t_program *program, int forks_amount)
{
	const char	*fork;
	sem_t		*sem_fork;

	fork = "sem_fork";
	sem_unlink(fork);
	sem_fork = sem_open(fork, O_CREAT | O_EXCL, 0666, forks_amount);
	if (sem_fork == SEM_FAILED)
		sem_creat_error("fork");
	program->fork = sem_fork;
}
