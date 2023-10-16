/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 14:07:04 by osarsari          #+#    #+#             */
/*   Updated: 2023/10/16 13:06:03 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	start_threads(t_philo *philo)
{
	int				i;

	i = 0;
	gettimeofday(&philo->data->start, NULL);
	while (i < philo->data->nbr)
	{
		philo[i].last_eat = philo->data->start;
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
	pthread_mutex_destroy(&philo->data->mutex_dead);
	pthread_mutex_destroy(&philo->data->mutex_write);
}
