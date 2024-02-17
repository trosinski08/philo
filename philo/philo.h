/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 17:05:20 by trosinsk          #+#    #+#             */
/*   Updated: 2024/02/17 20:48:20 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

# define MAX_PHILOS 1000

typedef struct s_philo
{
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
	pthread_t		thread;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	int				id;
	int				eating;
	int				meals_eaten; 
	int				number_of_philos;
	int				meals_number;
	int				*dead;
}					t_philo;

typedef struct s_program
{
	int				dead_flag;
	pthread_mutex_t	fork[MAX_PHILOS];
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	t_philo			*philos;
}					t_program;

//init.c
void	init_data(char **argv, t_philo *philos);
void	init_program(t_program *program, t_philo *philos, char **argv);
void	philos_init(t_philo *philos, t_program *program, char **argv);

//utils.c
int		ft_atoi(const char *num);
int		current_time(void);

//philo.c
void	*routine(void *arg);
// void	thread_init(t_program *program, t_philo *philos);
void	thread_init(t_program *program);


//monitor.c
void	*monitoring(void *arg);

//errors_msg.c
void	number_of_philos_error(void);
void	time_to_die_error(void);
void	time_to_eat_error(void);
void	time_to_sleep_error(void);
void	number_of_meals_error(void);

#endif