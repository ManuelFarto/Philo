/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_clear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafarto- <mafarto-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:14:47 by mafarto-          #+#    #+#             */
/*   Updated: 2025/04/17 09:43:49 by mafarto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_forks(pthread_mutex_t *forks, int num_philos)
{
	int	i;

	i = 0;
	while (i < num_philos)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

static void	init_philo_data(t_philo *philo, t_shared *shared, char **argv)
{
	philo->time_die = atol(argv[2]);
	philo->time_eat = atol(argv[3]);
	philo->time_sleep = atol(argv[4]);
	philo->last_meal = get_time_ms();
	philo->start_time = get_time_ms();
	philo->shared = shared;
}

void	init_philosophers(t_controller *controller, char **argv,
		int num_philos, int eats)
{
	int	i;

	i = 0;
	while (i < num_philos)
	{
		controller->philos[i].philo_num = i + 1;
		controller->philos[i].num_of_eats = eats;
		controller->philos[i].left_fork = &controller->forks[i];
		controller->philos[i].right_fork
			= &controller->forks[(i + 1) % num_philos];
		init_philo_data(&controller->philos[i], controller->shared, argv);
		pthread_mutex_init(&controller->philos[i].meal_mutex, NULL);
		i++;
	}
}

void	start_threads(t_philo *philos, pthread_t *threads, int num_philos)
{
	int	i;

	i = 0;
	while (i < num_philos)
	{
		pthread_create(&threads[i], NULL, philo_life, &philos[i]);
		i++;
	}
}

void	join_threads(pthread_t *threads, int num_philos)
{
	int	i;

	i = 0;
	while (i < num_philos)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}
