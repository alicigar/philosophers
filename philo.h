/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicigar < alicigar@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 16:23:45 by alicigar          #+#    #+#             */
/*   Updated: 2026/02/13 22:07:12 by alicigar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

//libs
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

struct	s_data;

typedef struct s_philo
{
	struct s_data	*data;
	int				id;
	int				meals;
	long			last_meal;
	pthread_t		thread;
	int				left_fork;
	int				right_fork;
	/*int				priority;*/
	pthread_mutex_t	meal_mutex;
}	t_philo;

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
int		initialize_all(t_data *data, int argc, char **argv);
void	cleanup(t_data *data);
int		check_death(t_data *data);
void	philo_think(t_philo *philo);
void	philo_eat(t_philo	*philo);
void	take_forks_even(t_philo *philo);
void	take_forks_odd(t_philo *philo);
void	philo_sleep(t_philo	*philo);
void	*philo_routine(void *arg);
int		check_philosopher_death(t_data *data, int i);
int		check_all_ate(t_data *data);
void	*monitor_routine(void	*arg);
int		start_simulation(t_data *data);

#endif
