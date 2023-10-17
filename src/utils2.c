/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:03:46 by osarsari          #+#    #+#             */
/*   Updated: 2023/10/17 14:29:06 by osarsari         ###   ########.fr       */
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

int	altruism(t_philo *philo)
{
	struct timeval	own_time;
	struct timeval	right_neighbor_time;
	struct timeval	left_neighbor_time;

	own_time = philo->last_eat;
	pthread_mutex_lock(&philo->data->mutex_write);
	if (philo->id == philo->data->nbr)
		right_neighbor_time = philo->data->last_eat[0];
	else
		right_neighbor_time = philo->data->last_eat[philo->id];
	if (philo->id == 1)
		left_neighbor_time = philo->data->last_eat[philo->data->nbr - 1];
	else
		left_neighbor_time = philo->data->last_eat[philo->id - 2];
	pthread_mutex_unlock(&philo->data->mutex_write);
	if (own_time.tv_sec * 1000 + own_time.tv_usec / 1000 > \
		right_neighbor_time.tv_sec * 1000 + right_neighbor_time.tv_usec / 1000 \
		|| own_time.tv_sec * 1000 + own_time.tv_usec / 1000 > \
		left_neighbor_time.tv_sec * 1000 + left_neighbor_time.tv_usec / 1000)
		return (1);
	return (0);
}
