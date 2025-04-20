/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafarto- <mafarto-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:17:04 by mafarto-          #+#    #+#             */
/*   Updated: 2025/04/20 20:43:22 by mafarto-         ###   ########.fr       */
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

int	validate_args(int argc, char **argv)
{
	if (argc <= 4 || argc > 6)
	{
		printf("Error: ./philo num_philos time_die time_eat time_sleep\n");
		return (1);
	}
	if (argv[1][0] == '0')
		return (1);
	if (argv[1][0] == '1' && !argv[1][1])
	{
		printf("%ld %d %s\n", get_time_ms() - get_time_ms(), 1, TAKEN_FORK);
		usleep(atoi(argv[2]));
		printf("%d %d %s\n", atoi(argv[2]), 1, DIED);
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
		pthread_mutex_destroy(&controller->philos[i].meal_mutex);
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

int	ft_isdigit(int argc, char **str)
{
	int	count;
	int	count1;

	count1 = 1;
	count = 0;
	while (str[count1])
	{
		count = 0;
		while (str[count1][count])
		{
			if (str[count1][count] < '0' || str[count1][count] > '9')
			{
				return (0);
			}
			count++;
		}
		count1++;
	}
	if (count1 != argc)
		return (0);
	return (1);
}
