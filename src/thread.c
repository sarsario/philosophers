/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:02:05 by osarsari          #+#    #+#             */
/*   Updated: 2023/10/17 14:11:34 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	start_thread(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->nbr)
	{
		gettimeofday(&philo[i].start, NULL);
		philo[i].last_eat = philo[i].start;
		pthread_mutex_lock(&philo[i].data->mutex_write);
		philo[i].data->last_eat[i] = philo[i].start;
		pthread_mutex_unlock(&philo[i].data->mutex_write);
		if (pthread_create(&philo[i].thread, NULL, routine, &philo[i]))
		{
			while (--i >= 0)
				pthread_detach(philo[i].thread);
			return (0);
		}
		i++;
	}
	return (1);
}

int	join_thread(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->nbr)
	{
		if (pthread_join(philo[i].thread, NULL))
		{
			while (i < philo->data->nbr)
				pthread_detach(philo[i++].thread);
			return (0);
		}
		i++;
	}
	return (1);
}
