/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_msg_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 13:50:37 by trosinsk          #+#    #+#             */
/*   Updated: 2024/03/18 13:39:23 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	number_error(char *str)
{
	printf("Error: wrong number of %s\n", str);
	exit(1);
}

void	time_error(char *str)
{
	printf("Error: wrong time to %s\n", str);
	exit(1);
}

void	input_error(void)
{
	printf("Error: wrong input format, use only numbers\n");
	exit(1);
}

void	thread_creat_error(t_program *program)
{
	printf("Thread no %d creation error\n", program->philos->id);
	exit(1);
}

void	sem_creat_error(char *str)
{
	printf("Semaphore %s creation error", str);
	exit(1);
}
