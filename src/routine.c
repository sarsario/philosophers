/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 16:10:21 by osarsari          #+#    #+#             */
/*   Updated: 2023/09/24 14:03:29 by osarsari         ###   ########.fr       */
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

static void	thinking(t_philo *philo)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	printf("%ld %d is thinking\n", now.tv_sec * 1000 + now.tv_usec / 1000,
		philo->id);
}

static void	sleeping(t_philo *philo)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	printf("%ld %d is sleeping\n", now.tv_sec * 1000 + now.tv_usec / 1000,
		philo->id);
	usleep(philo->data->t_sleep * 1000);
}

static void	eating(t_philo *philo)
{
	struct timeval	now;

	pthread_mutex_lock(&philo->left->mutex);
	gettimeofday(&now, NULL);
	printf("%ld %d has taken a fork\n", now.tv_sec * 1000 + now.tv_usec
		/ 1000, philo->id);
	thinking(philo);
	pthread_mutex_lock(&philo->right->mutex);
	gettimeofday(&now, NULL);
	printf("%ld %d has taken a fork\n", now.tv_sec * 1000 + now.tv_usec
		/ 1000, philo->id);
	printf("%ld %d is eating\n", now.tv_sec * 1000 + now.tv_usec / 1000,
		philo->id);
	philo->last_eat = now;
	usleep(philo->data->t_eat * 1000);
	philo->nb_eat++;
	pthread_mutex_unlock(&philo->left->mutex);
	pthread_mutex_unlock(&philo->right->mutex);
}

void	*routine(void *arg)
{
	t_philo			*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (is_dead(philo, philo->last_eat))
			return (NULL);
		thinking(philo);
		eating(philo);
		if (philo->data->nbr_eat != -1 && philo->nb_eat == philo->data->nbr_eat)
			return (NULL);
		sleeping(philo);
	}
}
