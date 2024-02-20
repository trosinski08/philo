/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_msg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 13:50:37 by trosinsk          #+#    #+#             */
/*   Updated: 2024/02/20 01:29:35 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	time_to_die_error(void)
{
	printf("Error: wrong time to die\n");
	exit(1);
}

void	time_to_eat_error(void)
{
	printf("Error: wrong time to eat\n");
	exit(1);
}

void	time_to_sleep_error(void)
{
	printf("Error: wrong time to sleep\n");
	exit(1);
}

void	number_of_meals_error(void)
{
	printf("Error: wrong number of meals\n");
	exit(1);
}

void	thread_creat_error(t_program *program)
{
	printf("Thread creation error");
	mutex_destructor(program);
	exit(1);
}
