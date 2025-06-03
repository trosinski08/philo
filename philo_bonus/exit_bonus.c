/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 10:45:00 by trosinsk          #+#    #+#             */
/*   Updated: 2024/06/02 10:45:00 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	exit_program(t_program *program)
{
	sem_close(program->fork);
	sem_close(program->sem_dead);
	sem_close(program->sem_eating);
	sem_close(program->sem_meal);
	sem_close(program->sem_print);
	sem_unlink("sem_fork");
	sem_unlink("sem_dead");
	sem_unlink("sem_eating");
	sem_unlink("sem_meal");
	sem_unlink("sem_print");
	free(program->pids);
} 