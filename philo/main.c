/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 16:29:49 by trosinsk          #+#    #+#             */
/*   Updated: 2024/02/21 01:02:18 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	argv_checker(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		number_error("arguments");
	if ((ft_atoi(argv[1]) < 1) || ft_atoi(argv[1]) > MAX_PHILOS)
		number_error("philosophers");
	if (ft_atoi(argv[2]) < 1)
		time_error("die");
	if (ft_atoi(argv[3]) < 1)
		time_error("eat");
	if (ft_atoi(argv[4]) < 1)
		time_error("sleep");
	if (argc == 6 && ft_atoi(argv[5]) < 1)
		number_error("meals");
	argv_validator(argc, argv);
}

int	main(int argc, char **argv)
{
	t_philo		philos[MAX_PHILOS];
	t_program	program;

	argv_checker(argc, argv);
	init_program(&program, philos, argv);
	philos_init(philos, &program, argv);
	thread_init(&program);
	mutex_destructor(&program);
	return (0);
}
