/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafarto- <mafarto-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:17:04 by mafarto-          #+#    #+#             */
/*   Updated: 2025/04/08 21:06:12 by mafarto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday (&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		((unsigned char *)b)[i] = c;
		i++;
	}
	return (b);
}

int	validate_args(int argc)
{
	if (argc < 5 || argc > 6)
	{
		printf("./philo num_philos time_dietime_eat time_sleep\n");
		return (1);
	}
	return (0);
}

void	cleanup(t_controller *controller, int num_philos)
{
	int	i;

	i = 0;
	while (i < num_philos)
	{
		pthread_mutex_destroy(&controller->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&controller->shared->stop_mutex);
	pthread_mutex_destroy(&controller->shared->print_mutex);
	free(controller->forks);
	free(controller->philos);
	free(controller->threads);
	free(controller->shared);
	free(controller);
}
