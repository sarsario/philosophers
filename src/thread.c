/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:02:05 by osarsari          #+#    #+#             */
/*   Updated: 2023/10/18 15:37:54 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	start_thread(t_philo *philo)
{
	int	i;

	if (philo->data->nbr == 1)
		return (1);
	i = 0;
	while (i < philo->data->nbr)
	{
		gettimeofday(&philo[i].last_eat, NULL);
		pthread_mutex_lock(&philo[i].data->mutex_write);
		philo[i].data->last_eat[i] = philo[i].last_eat;
		pthread_mutex_unlock(&philo[i].data->mutex_write);
		if (i % 2 == 0)
			philo[i].ate = 1;
		if (pthread_create(&philo[i].thread, NULL, &routine, &philo[i]))
		{
			force_death(&philo[i]);
			while (i-- > 0)
				pthread_join(philo[i].thread, NULL);
			return (0);
		}
		i++;
	}
	return (1);
}

int	join_thread(t_philo *philo)
{
	int	i;

	if (philo->data->nbr == 1)
		return (1);
	i = 0;
	while (i < philo->data->nbr)
	{
		if (pthread_join(philo[i].thread, NULL))
		{
			force_death(&philo[i]);
			pthread_detach(philo[i].thread);
		}
		i++;
	}
	return (1);
}
