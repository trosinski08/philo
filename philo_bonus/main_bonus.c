/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 21:25:21 by trosinsk          #+#    #+#             */
/*   Updated: 2024/03/18 13:57:13 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	argv_checker(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		number_error("arguments");
	if ((ft_atoi(argv[1]) < 1) || ft_atoi(argv[1]) > MAX_PHILO)
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
	t_philo		philos[MAX_PHILO];
	t_program	program;

	argv_checker(argc, argv);
	init_program(&program, philos, argv);
	philos_init(philos, &program, argv);
	process_init(&program);
	return (0);
}
