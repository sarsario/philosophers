/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 22:54:52 by osarsari          #+#    #+#             */
/*   Updated: 2023/09/29 23:34:12 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	get_time_diff(struct timeval start, struct timeval end)
{
	return ((end.tv_sec * 1000 + end.tv_usec / 1000) - (start.tv_sec * 1000
			+ start.tv_usec / 1000));
}

int	dead(t_philo *philo)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	pthread_mutex_lock(&philo->data->death);
	if (get_time_diff(philo->last_eat, now) > philo->data->t_die)
	{
		printf("%ld %d died\n", get_time_diff(philo->data->start, now),
			philo->id);
		philo->data->dead = 1;
		pthread_mutex_unlock(&philo->data->death);
		return (1);
	}
	if (philo->data->dead)
	{
		pthread_mutex_unlock(&philo->data->death);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->death);
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (dead(philo))
			break ;
		if (!take_forks(philo))
			break ;
		if (!eat(philo))
			break ;
		if (!sleep(philo))
			break ;
		if (!think(philo))
			break ;
	}
	return (NULL);
}
