/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 16:10:21 by osarsari          #+#    #+#             */
/*   Updated: 2023/09/24 19:31:27 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	is_dead(t_philo *philo)
{
	struct timeval	now;

	pthread_mutex_lock(&philo->data->mutex);
	if (philo->data->dead)
	{
		pthread_mutex_unlock(&philo->data->mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->mutex);
	gettimeofday(&now, NULL);
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

static int	thinking(t_philo *philo)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	if (is_dead(philo))
		return (0);
	printf("%ld %d is thinking\n", now.tv_sec * 1000 + now.tv_usec / 1000,
		philo->id);
	usleep(10);
	return (1);
}

static int	sleeping(t_philo *philo)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	if (is_dead(philo))
		return (0);
	printf("%ld %d is sleeping\n", now.tv_sec * 1000 + now.tv_usec / 1000,
		philo->id);
	usleep(philo->data->t_sleep * 1000);
	if (is_dead(philo))
		return (0);
	return (1);
}

static int	eating(t_philo *philo)
{
	struct timeval	now;

	if (is_dead(philo))
		return (0);
	pthread_mutex_lock(&philo->left->mutex);
	gettimeofday(&now, NULL);
	if (is_dead(philo))
		pthread_mutex_unlock(&philo->left->mutex);
	if (is_dead(philo))
		return (0);
	printf("%ld %d has taken a fork\n", now.tv_sec * 1000 + now.tv_usec
		/ 1000, philo->id);
	thinking(philo);
	if (is_dead(philo))
		pthread_mutex_unlock(&philo->left->mutex);
	if (is_dead(philo))
		return (0);
	pthread_mutex_lock(&philo->right->mutex);
	gettimeofday(&now, NULL);
	if (is_dead(philo))
		pthread_mutex_unlock(&philo->right->mutex);
	if (is_dead(philo))
		return (0);
	printf("%ld %d has taken a fork\n", now.tv_sec * 1000 + now.tv_usec
		/ 1000, philo->id);
	printf("%ld %d is eating\n", now.tv_sec * 1000 + now.tv_usec / 1000,
		philo->id);
	philo->last_eat = now;
	usleep(philo->data->t_eat * 1000);
	philo->nb_eat++;
	pthread_mutex_unlock(&philo->left->mutex);
	pthread_mutex_unlock(&philo->right->mutex);
	return (1);
}

void	*routine(void *arg)
{
	t_philo			*philo;
	struct timeval	now;

	philo = (t_philo *)arg;
	while (1)
	{
		if (philo->data->nbr == 1)
		{
			pthread_mutex_lock(&philo->left->mutex);
			gettimeofday(&now, NULL);
			printf("%ld %d has taken a fork\n", now.tv_sec * 1000 + now.tv_usec
				/ 1000, philo->id);
			thinking(philo);
			usleep(philo->data->t_die * 1000);
			philo->last_eat.tv_sec = 0;
			philo->last_eat.tv_usec = 0;
			pthread_mutex_unlock(&philo->left->mutex);
		}
		if (is_dead(philo))
			return (NULL);
		if (!thinking(philo))
			return (NULL);
		if (!eating(philo))
			return (NULL);
		if (philo->data->nbr_eat != -1 && philo->nb_eat == philo->data->nbr_eat)
			return (NULL);
		if (!sleeping(philo))
			return (NULL);
	}
}

// Routine
// 1. Think
// 1.1 Check if dead
// 2. Take forks
// 2.1 Check if dead
// 3. Eat
// 3.1 Check if dead
// 4. Sleep
// 4.1 Check if dead
