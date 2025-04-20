/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafarto- <mafarto-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 18:12:24 by mafarto-          #+#    #+#             */
/*   Updated: 2025/03/07 18:28:56 by mafarto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_life(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->philo_num % 2 == 0)
		usleep(10000);
	while (1)
	{
		pthread_mutex_lock(&philo->shared->stop_mutex);
		if (philo->shared->stop_simulation)
			return (pthread_mutex_unlock(&philo->shared->stop_mutex), NULL);
		pthread_mutex_unlock(&philo->shared->stop_mutex);
		eat(philo);
		philo->num_of_eats -= (philo->num_of_eats > 0);
		if (philo->num_of_eats == 0)
			return (time_for_lunch(philo), NULL);
		sleep_think(philo);
	}
}

void	*monitor(void *arg)
{
	t_philo	*philos;
	int		i;
	long	time_since_meal;

	philos = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&philos->shared->stop_mutex);
		if (philos->shared->stop_simulation)
			return (pthread_mutex_unlock(&philos->shared->stop_mutex), NULL);
		i = 0;
		while (i < philos->shared->all_philo)
		{
			pthread_mutex_lock (&philos[i].meal_mutex);
			time_since_meal = get_time_ms() - philos[i].last_meal;
			if (time_since_meal > philos[i].time_die)
				return (philo_die (philos, i), NULL);
			pthread_mutex_unlock(&philos[i].meal_mutex);
			i++;
		}
		pthread_mutex_unlock(&philos->shared->stop_mutex);
		usleep(10000);
	}
	return (NULL);
}

void	exit_clean(t_controller **controller)
{
	free((*controller)->shared);
	free((*controller)->forks);
	free((*controller)->philos);
	free((*controller)->threads);
	free(*controller);
}

t_controller	*init_controller(int num_philos)
{
	t_controller	*controller;

	controller = malloc(sizeof(t_controller));
	if (!controller)
		return (NULL);
	ft_memset(controller, 0, sizeof(t_controller));
	controller->shared = malloc(sizeof(t_shared));
	if (!controller->shared)
		return (free(controller), NULL);
	ft_memset(controller->shared, 0, sizeof(t_shared));
	controller->forks = malloc(sizeof(pthread_mutex_t) * num_philos);
	controller->philos = malloc(sizeof(t_philo) * num_philos);
	controller->threads = malloc(sizeof(pthread_t) * num_philos);
	if (!controller->forks || !controller->philos || !controller->threads)
	{
		exit_clean(&controller);
		return (NULL);
	}
	controller->shared->stop_simulation = 0;
	controller->shared->finished_eating = 0;
	controller->shared->all_philo = num_philos;
	pthread_mutex_init(&controller->shared->stop_mutex, NULL);
	pthread_mutex_init(&controller->shared->print_mutex, NULL);
	return (controller);
}

int	main(int argc, char **argv)
{
	t_controller	*controller;
	pthread_t		monitor_thread;
	int				num_philos;
	int				num_of_eats;

	if (validate_args(argc, argv))
		return (1);
	if (ft_isdigit(argc, argv) == 0)
		return (printf("Error: One or more invalid character\n"), 1);
	num_philos = atoi(argv[1]);
	if (argc == 6)
		num_of_eats = atoi(argv[5]);
	else
		num_of_eats = -1;
	controller = init_controller(num_philos);
	if (!controller)
		return (printf("Error: Memory allocation error\n"), 1);
	init_forks(controller->forks, num_philos);
	init_philosophers(controller, argv, num_philos, num_of_eats);
	start_threads(controller->philos, controller->threads, num_philos);
	pthread_create(&monitor_thread, NULL, monitor, controller->philos);
	join_threads(controller->threads, num_philos);
	pthread_join(monitor_thread, NULL);
	return (cleanup(controller, num_philos), 0);
}
/*
./philo 1 800 200 200
./philo 5 800 200 200
./philo 5 800 200 200 7 >o
grep <o "1 is eating" | wc -l
grep <o "2 is eating" | wc -l
grep <o "3 is eating" | wc -l
grep <o "4 is eating" | wc -l
grep <o "5 is eating" | wc -l
./philo 4 410 200 200
./philo 4 310 200 100
./philo 2 310 200 100 */