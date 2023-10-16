/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_sleep.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 22:46:04 by osarsari          #+#    #+#             */
/*   Updated: 2023/10/16 13:08:15 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	m_sleep(t_philo *philo, int ms)
{
	struct timeval	start;

	gettimeofday(&philo->now, NULL);
	start = philo->now;
	while (philo->now.tv_sec * 1000 + philo->now.tv_usec / 1000
		- start.tv_sec * 1000 - start.tv_usec / 1000 < ms)
	{
		pthread_mutex_lock(&philo->data->mutex_dead);
		if (philo->data->dead)
		{
			pthread_mutex_unlock(&philo->data->mutex_dead);
			return (0);
		}
		pthread_mutex_unlock(&philo->data->mutex_dead);
		usleep(100);
		gettimeofday(&philo->now, NULL);
	}
	return (1);
}
