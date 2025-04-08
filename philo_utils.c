/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafarto- <mafarto-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:20:47 by mafarto-          #+#    #+#             */
/*   Updated: 2025/04/08 21:05:52 by mafarto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, TAKEN_FORK);
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, TAKEN_FORK);
	print_status(philo, EATING);
	pthread_mutex_lock(&philo->shared->stop_mutex);
	philo->last_meal = get_time_ms();
	pthread_mutex_unlock(&philo->shared->stop_mutex);
	usleep(philo->time_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	sleep_think(t_philo *philo)
{
	print_status(philo, SLEEPING);
	usleep(philo->time_sleep * 1000);
	print_status(philo, THINKING);
}

void	time_for_lunch(t_philo	*philo)
{
	pthread_mutex_lock(&philo->shared->stop_mutex);
	philo->shared->finished_eating++;
	if (philo->shared->finished_eating == philo->shared->all_philo)
		philo->shared->stop_simulation = 1;
	pthread_mutex_unlock (&philo->shared->stop_mutex);
}

void	print_status(t_philo *philo, const char *msg)
{
	pthread_mutex_lock(&philo->shared->print_mutex);
	if (!philo->shared->stop_simulation)
		printf("%ld %d %s\n", get_time_ms() - philo->start_time,
			philo->philo_num, msg);
	pthread_mutex_unlock(&philo->shared->print_mutex);
}

void	philo_die(t_philo *philos, int i)
{
	print_status(&philos[i], DIED);
	philos->shared->stop_simulation = 1;
	pthread_mutex_unlock(&philos->shared->stop_mutex);
}
