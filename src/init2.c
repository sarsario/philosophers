/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 20:37:24 by osarsari          #+#    #+#             */
/*   Updated: 2023/09/30 23:15:16 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*free_forks(t_fork *forks)
{
	if (forks)
		free(forks);
	return (NULL);
}

void	*free_philos(t_philo *philos)
{
	if (philos)
		free(philos);
	return (NULL);
}

t_fork	*mutex_forks(t_fork *forks, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (pthread_mutex_init(&forks[i].mutex, NULL) != 0)
		{
			while (i > 0)
			{
				i--;
				pthread_mutex_destroy(&forks[i].mutex);
			}
			return (free_forks(forks));
		}
		i++;
	}
	return (forks);
}

t_data	*mutex_data(t_data *data)
{
	if (pthread_mutex_init(&data->m_dead, NULL) != 0)
		return (free_data(data));
	if (pthread_mutex_init(&data->m_eat, NULL) != 0)
	{
		pthread_mutex_destroy(&data->m_dead);
		return (free_data(data));
	}
	if (pthread_mutex_init(&data->m_write, NULL) != 0)
	{
		pthread_mutex_destroy(&data->m_dead);
		pthread_mutex_destroy(&data->m_eat);
		return (free_data(data));
	}
	return (data);
}