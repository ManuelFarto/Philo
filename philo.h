/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafarto- <mafarto-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:10:49 by mafarto-          #+#    #+#             */
/*   Updated: 2025/04/08 21:13:12 by mafarto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

// ----------- DEFINE ---------------- //
# define THINKING "is thinking"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define TAKEN_FORK "has taken a fork"
# define DIED "died"

// ----------- STRUCTS -------------- //
typedef struct s_shared
{
	int				stop_simulation;
	int				finished_eating;
	int				all_philo;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	print_mutex;
}			t_shared;

typedef struct s_philo
{
	int				philo_num;
	long			time_die;
	long			time_eat;
	long			time_sleep;
	int				num_of_eats;
	long			last_meal;
	long			start_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_shared		*shared;
}			t_philo;

typedef struct s_controller
{
	pthread_t		*threads;
	pthread_mutex_t	*forks;
	t_philo			*philos;
	t_shared		*shared;
}			t_controller;

// ----------- FUNTIONS ---------- //

// Main
int				main(int argc, char **argv);
void			exit_clean(t_controller **controller);
t_controller	*init_controller(int num_philos);
void			*monitor(void *arg);
void			*philo_life(void *arg);

// Philo Utils
void			eat(t_philo *philo);
void			sleep_think(t_philo *philo);
void			time_for_lunch(t_philo *philo);
void			print_status(t_philo *philo, const char *msg);
void			philo_die(t_philo *philos, int i);

// Init and clean
void			init_forks(pthread_mutex_t *forks, int num_philos);
void			init_philosophers(t_controller *controller, char **argv,
					int num_philos, int eats);
void			start_threads(t_philo *philos, pthread_t *threads,
					int num_philos);
void			join_threads(pthread_t *threads, int num_philos);

// Utils
long			get_time_ms(void);
void			*ft_memset(void *b, int c, size_t len);
int				validate_args(int argc);
void			cleanup(t_controller *controller, int num_philos);

#endif