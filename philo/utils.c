/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 19:17:57 by trosinsk          #+#    #+#             */
/*   Updated: 2024/02/17 16:17:29 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int	current_time(void)
{
	struct timeval	tv;
	int				time_in_sec;

	gettimeofday(&tv, NULL);
	time_in_sec = tv.tv_usec;
	return (time_in_sec);
}