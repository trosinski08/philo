/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_msg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 13:50:37 by trosinsk          #+#    #+#             */
/*   Updated: 2024/02/21 01:09:00 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	printf("Thread creation error");
	mutex_destructor(program);
	exit(1);
}

void	mutex_creat_error(t_program *program, char *str)
{
	printf("Mutex %s creation error", str);
	mutex_destructor(program);
	exit(1);
}
