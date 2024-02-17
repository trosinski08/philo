/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 16:29:49 by trosinsk          #+#    #+#             */
/*   Updated: 2024/02/17 20:48:40 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	arg_number_error(void)
{
	printf("Error: wrong number of arguments\n");
	exit(1);
}

void	argv_validator(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				printf("wrong imput format, use only numbers\n");
			j++;
		}
		i++;
	}
}

void	argv_checker(int argc, char **argv)
{

	if (argc < 5 || argc > 6)
		arg_number_error();
	if ((ft_atoi(argv[1]) < 1) || ft_atoi(argv[1]) > MAX_PHILOS)
		number_of_philos_error();
	if (ft_atoi(argv[2]) < 1)
		time_to_die_error();
	if (ft_atoi(argv[3]) < 1)
		time_to_eat_error();
	if (ft_atoi(argv[4]) < 1)
		time_to_sleep_error();
	if (argc == 6 && ft_atoi(argv[5]) < 1)
		number_of_meals_error();
	argv_validator(argc, argv);
}

int	main(int argc, char **argv)
{
	t_philo		philos[MAX_PHILOS];
	t_program	program;

	argv_checker(argc, argv);
	init_program(&program, philos, argv);
	philos_init(philos, &program, argv);
	// thread_init(&program, philos);
	thread_init(&program);
	return (0);
}
