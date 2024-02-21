/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 17:05:20 by trosinsk          #+#    #+#             */
/*   Updated: 2024/02/21 04:01:04 by trosinsk         ###   ########.fr       */
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
# define T "is thinking"
# define S "is sleeping"
# define E "is eating"
# define F "has taken a fork"
# define D "died"

typedef struct s_philo
{
	int				id;
	int				dining;
	int				meals_eaten;
	int				philos_amount;
	int				meals_number;
	int				*dead;
	size_t			last_meal_time;
	size_t			die_time;
	size_t			eat_time;
	size_t			sleep_time;
	size_t			start_time;
	pthread_t		thread;
	pthread_mutex_t	*right_f;
	pthread_mutex_t	*left_f;
	pthread_mutex_t	*mutex_eating;
	pthread_mutex_t	*mutex_print;
	pthread_mutex_t	*mutex_dead;
	pthread_mutex_t	*mutex_meal;
}					t_philo;

typedef struct s_program
{
	int				dead_flag;
	pthread_mutex_t	fork[MAX_PHILOS];
	pthread_mutex_t	mutex_dead;
	pthread_mutex_t	mutex_eating;
	pthread_mutex_t	mutex_meal;
	pthread_mutex_t	mutex_print;
	t_philo			*philos;
}					t_program;

//init.c
void	init_program(t_program *program, t_philo *philos, char **argv);
void	philos_init(t_philo *philos, t_program *program, char **argv);
void	init_data(char **argv, t_philo *philos);
void	thread_init(t_program *program);

//utils.c
int		ft_atoi(const char *num);
void	argv_validator(int argc, char **argv);
size_t	current_time(void);
size_t	ft_usleep(size_t milliseconds);
void	mutex_destructor(t_program *program);

//utils2.c
void	handle_1(t_philo *philos);
void	mutex_dead(t_program *program, int i);
void	printing_lock(t_philo *philos, char *str);
int		is_eating(t_philo *philos, int i);

//philo.c
void	*routine(void *arg);

//big_brother.c
void	*supervising(void *arg);
int		discontinue(t_philo *philos);

//errors_msg.c
void	number_error(char *str);
void	time_error(char *str);
void	input_error(void);
void	thread_creat_error(t_program *program);
void	mutex_creat_error(t_program *program, char *str);

#endif