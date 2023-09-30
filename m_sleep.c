/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_sleep.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 23:19:37 by osarsari          #+#    #+#             */
/*   Updated: 2023/09/30 23:27:09 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	m_sleep(t_philo *philo, int time)
{
	int	start;

	start = get_time();
	usleep(100);
	while (get_time() - start < time)
	{
		pthread_mutex_lock(philo->data->m_dead);
		if (philo->data->dead)
		{
			pthread_mutex_unlock(philo->data->m_dead);
			return (0);
		}
		pthread_mutex_unlock(philo->data->m_dead);
		usleep(100);
	}
	return (1);
}