/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicigar < alicigar@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 16:23:45 by alicigar          #+#    #+#             */
/*   Updated: 2026/01/27 19:03:26 by alicigar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

//libs
# include <string.h>//-> memset
# include <stdio.h>//-> printf
# include <stdlib.h>//-> malloc, free 
# include <unistd.h>//-> write, usleep 
# include <sys/time.h>//-> gettimeofday (te lo da en microsegundos y lo pide en milisegundos)
# include <pthread.h>/*-> pthread_create, pthread_detach, 
pthread_join, pthread_mutex_init, pthread_mutex_destroy,
pthread_mutex_lock, pthread_mutex_unlock*/

//structs
struct	s_data;

//ESTRUCTURA DEL FILOSOFO
//id ✅
//contador de comidas ✅
//tiempo de ultima comida ✅
//puntero a la ESTRUCTURA GENERAL ✅
//su hilo ✅
//indices de tenedor izqdo y tenedor dcho ✅

typedef struct s_philo
{
	struct s_data	*data;
	int				id;
	int				meals;
	long			last_meal; //long por overflow con int
	pthread_t		thread;
	int				left_fork;
	int				right_fork;
}	t_philo;

//ESTRUCTURA GENERAL
//parametros de entrada ✅
//array de mutexes/tenedores 
//mutex para imprimir 
//array de filosofos 
//tiempo de inicio 
//flag de muerte

typedef struct s_data
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	pthread_mutex_t	*forks;
	pthread_mutex_t	log_mutex;
	pthread_mutex_t	death_mutex;
	t_philo			*philos;
	long			start_time;
	int				dead;
}	t_data;

//functions

int		ft_isdigit(int n);
int		ft_atoi(const char *nptr);
int		is_valid_arg(const char *str);
int		input_checker(int argc, char **argv);
long	get_time(void);
void	safe_sleep(long time_in_ms);
int		init_data(t_data *data, int argc, char **argv);
int		init_forks(t_data *data);
int		init_philos(t_data *data);
void	cleanup(t_data *data);

#endif
