/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 14:07:04 by osarsari          #+#    #+#             */
/*   Updated: 2023/09/30 11:17:57 by osarsari         ###   ########.fr       */
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
		i++;
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
	pthread_mutex_destroy(&philo->data->full);
	pthread_mutex_destroy(&philo->data->death);
}
