/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 14:07:04 by osarsari          #+#    #+#             */
/*   Updated: 2023/10/14 13:42:07 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	start_threads(t_philo *philo)
{
	int				i;
	struct timeval	time;

	i = 0;
	while (i < philo->data->nbr)
	{
		gettimeofday(&time, NULL);
		philo[i].last_eat = time;
		if (pthread_create(&philo[i].thread, NULL, routine, &philo[i]))
		{
			while (i > 0)
			{
				i--;
				pthread_detach(philo[i].thread);
			}
			return (0);
		}
		i += 2;
	}
	i = 1;
	gettimeofday(&time, NULL);
	while (i < philo->data->nbr)
	{
		printf("%ld %d is thinking\n", time.tv_sec * 1000
			+ time.tv_usec / 1000, i + 1);
		i += 2;
	}
	usleep(1000 * philo->data->t_eat);
	i = 1;
	while (i < philo->data->nbr)
	{
		gettimeofday(&time, NULL);
		philo[i].last_eat = time;
		if (pthread_create(&philo[i].thread, NULL, routine, &philo[i]))
		{
			while (i > 0)
			{
				i--;
				pthread_detach(philo[i].thread);
			}
			return (0);
		}
		i += 2;
	}
	return (1);
}

int	start_error(t_philo *philo)
{
	deep_free(philo);
	return (ft_perror("Error: could not create thread\n"));
}

int	join_threads(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->nbr)
	{
		if (pthread_join(philo[i].thread, NULL))
		{
			while (i >= 0)
			{
				pthread_detach(philo[i].thread);
				i--;
			}
			return (0);
		}
		i++;
	}
	return (1);
}

int	join_error(t_philo *philo)
{
	deep_free(philo);
	return (ft_perror("Error: could not join thread\n"));
}

void	destroy_mutex(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->nbr)
	{
		pthread_mutex_destroy(&philo->data->forks[i].mutex);
		i++;
	}
	pthread_mutex_destroy(&philo->data->mutex);
}
