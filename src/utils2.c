/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:03:46 by osarsari          #+#    #+#             */
/*   Updated: 2023/10/16 16:40:45 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	time_diff(struct timeval *start, struct timeval *now)
{
	return ((now->tv_sec * 1000 + now->tv_usec / 1000)
		- (start->tv_sec * 1000 + start->tv_usec / 1000));
}

int	m_sleep(t_philo *philo, int time)
{
	gettimeofday(&philo->start, NULL);
	philo->now = philo->start;
	while (time_diff(&philo->start, &philo->now) < time)
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
