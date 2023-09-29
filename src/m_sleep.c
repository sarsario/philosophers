/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_sleep.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 22:46:04 by osarsari          #+#    #+#             */
/*   Updated: 2023/09/24 23:00:44 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	m_sleep(t_philo *philo, int ms)
{
	struct timeval	start;
	struct timeval	now;

	gettimeofday(&start, NULL);
	now = start;
	while (now.tv_sec * 1000 + now.tv_usec / 1000 - start.tv_sec * 1000
		- start.tv_usec / 1000 < ms)
	{
		pthread_mutex_lock(&philo->data->mutex);
		if (philo->data->dead)
		{
			pthread_mutex_unlock(&philo->data->mutex);
			return (0);
		}
		pthread_mutex_unlock(&philo->data->mutex);
		usleep(100);
		gettimeofday(&now, NULL);
	}
	return (1);
}