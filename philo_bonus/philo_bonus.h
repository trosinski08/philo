/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 21:22:56 by trosinsk          #+#    #+#             */
/*   Updated: 2024/03/18 14:24:30 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/time.h>

# define MAX_PHILO 600
# define T "is thinking"
# define S "is sleeping"
# define E "is eating"
# define F "has taken a fork"
# define D "died"

typedef struct s_philo
{
	int			id;
	int			dining;
	int			meals_eaten;
	int			philos_amount;
	int			meals_number;
	int			*dead;
	size_t		last_meal_time;
	size_t		die_time;
	size_t		eat_time;
	size_t		sleep_time;
	size_t		start_time;
	pthread_t	thread;
	sem_t		**fork;
	sem_t		**sem_eating;
	sem_t		**sem_print;
	sem_t		**sem_dead;
	sem_t		**sem_meal;
}					t_philo;

typedef struct s_program
{
	int		dead_flag;
	sem_t	*fork;
	sem_t	*sem_dead;
	sem_t	*sem_eating;
	sem_t	*sem_meal;
	sem_t	*sem_print;
	t_philo	*philos;
}					t_program;

//init_bonus.c
void	init_program(t_program *program, t_philo *philos, char **argv);
void	philos_init(t_philo *philos, t_program *program, char **argv);
void	process_init(t_program *program);
void	init_data(char **argv, t_philo *philos);
void	big_brother_init(t_program *program);

//sem_init_bonus.c
void	sem_dead_init(t_program *program);
void	sem_eating_init(t_program *program);
void	sem_meal_init(t_program *program);
void	sem_print_init(t_program *program);
void	sem_fork_init(t_program *program, int philos_amount);

//routine_bonus.c
void	*routine(t_philo *philos);

//big_brother_bonus.c
void	*supervising(void *arg);
int		discontinue(t_philo *philos);

//utils_bonus.c
int		ft_atoi(const char *num);
void	argv_validator(int argc, char **argv);
size_t	current_time(void);
size_t	ft_usleep(size_t milliseconds);

//utils2_bonus.c
void	handle_1(t_philo *philos);
void	sem_dead(t_program *program, int i);
void	printing_lock(t_philo *philos, char *str);
int		is_eating(t_philo *philos, int i);

//errors_msg_bonus.c
void	number_error(char *str);
void	time_error(char *str);
void	input_error(void);
void	thread_creat_error(t_program *program);
void	sem_creat_error(char *str);

#endif