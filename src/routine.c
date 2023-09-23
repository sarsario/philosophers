/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 16:10:21 by osarsari          #+#    #+#             */
/*   Updated: 2023/09/23 16:42:45 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	is_dead(t_philo *philo, struct timeval now)
{
	if (now.tv_sec * 1000 + now.tv_usec / 1000 - philo->last_eat.tv_sec
		* 1000 - philo->last_eat.tv_usec / 1000 > philo->data->t_die)
	{
		pthread_mutex_lock(&philo->data->mutex);
		printf("%ld %d died\n", now.tv_sec * 1000 + now.tv_usec / 1000,
			philo->id);
		philo->data->dead = 1;
		pthread_mutex_unlock(&philo->data->mutex);
		return (1);
	}
	return (0);
}

void	*routine(void *arg)
{
	t_philo			*philo;
	struct timeval	now;

	philo = (t_philo *)arg;
	while (1)
	{
		gettimeofday(&now, NULL);
		if (is_dead(philo, now))
			return (NULL);
		pthread_mutex_lock(&philo->left->mutex);
		printf("%ld %d has taken a fork\n", now.tv_sec * 1000 + now.tv_usec
			/ 1000, philo->id);
		printf("%d is thinking\n", philo->id);
		pthread_mutex_lock(&philo->right->mutex);
		printf("%ld %d has taken a fork\n", now.tv_sec * 1000 + now.tv_usec
			/ 1000, philo->id);
		printf("%d is eating\n", philo->id);
		gettimeofday(&philo->last_eat, NULL);
		usleep(philo->data->t_eat * 1000);
		pthread_mutex_unlock(&philo->left->mutex);
		pthread_mutex_unlock(&philo->right->mutex);
		if (philo->nb_eat == philo->data->nbr_eat)
			return (NULL);
		gettimeofday(&now, NULL);
		printf("%ld %d is sleeping\n", now.tv_sec * 1000 + now.tv_usec / 1000,
			philo->id);
	}
}
