/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 19:17:57 by trosinsk          #+#    #+#             */
/*   Updated: 2024/03/17 22:29:56 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_atoi(const char *num)
{
	int	i;
	int	sign;
	int	conv_value;

	i = 0;
	sign = 1;
	conv_value = 0;
	while ((num[i] >= 9 && num[i] <= 13) || num[i] == 32)
		i++;
	if (num[i] == '-' || num[i] == '+')
	{
		if (num[i] == '-')
			sign = -sign;
		i++;
	}
	while (num[i] >= '0' && num[i] <= '9')
	{
		conv_value = (num[i] - '0') + (conv_value * 10);
		i++;
	}
	return (conv_value * sign);
}

void	argv_validator(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		if (argv[i][0] == 48 && argv[i][1])
			input_error();
		while (argv[i][j])
		{
			if (argv[i][j] < 48 || argv[i][j] > 57)
				input_error();
			j++;
		}
		i++;
	}
}

size_t	current_time(void)
{
	struct timeval	tv;
	size_t			time_in_sec;
	size_t			time_in_usec;

	gettimeofday(&tv, NULL);
	time_in_sec = tv.tv_sec;
	time_in_usec = tv.tv_usec;
	return (time_in_sec * 1000 + time_in_usec / 1000);
}

size_t	ft_usleep(size_t time)
{
	size_t	start;

	start = current_time();
	while ((current_time() - start) < time)
		usleep(400);
	return (0);
}
