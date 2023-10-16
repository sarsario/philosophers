/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 16:10:21 by osarsari          #+#    #+#             */
/*   Updated: 2023/10/16 13:04:24 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	someone_died(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_dead);
	if (philo->data->dead)
	{
		pthread_mutex_unlock(&philo->data->mutex_dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->mutex_dead);
	return (0);
}

void	print_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_write);
	gettimeofday(&philo->now, NULL);
	printf("%ld %d has taken a fork\n", philo->now.tv_sec * 1000
		+ philo->now.tv_usec / 1000, philo->id);
	pthread_mutex_unlock(&philo->data->mutex_write);
}

int	take_forks(t_philo *philo)
{
	if (someone_died(philo))
		return (0);
	pthread_mutex_lock(&philo->left->mutex);
	if (!philo->left->in_use)
		philo->left->in_use = philo->id;
	else
	{
		pthread_mutex_unlock(&philo->left->mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->left->mutex);
	print_fork(philo);
	pthread_mutex_lock(&philo->right->mutex);
	if (!philo->right->in_use)
		philo->right->in_use = philo->id;
	else
	{
		pthread_mutex_unlock(&philo->right->mutex);
		return (1);
	}
	print_fork(philo);
	pthread_mutex_unlock(&philo->right->mutex);
	return (1);
}

int	eating(t_philo *philo)
{
	if (someone_died(philo))
		return (0);
	pthread_mutex_lock(&philo->left->mutex);
	if (philo->left->in_use != philo->id)
	{
		pthread_mutex_unlock(&philo->left->mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->left->mutex);
	pthread_mutex_lock(&philo->right->mutex);
	if (philo->right->in_use != philo->id)
	{
		pthread_mutex_unlock(&philo->right->mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->right->mutex);
	pthread_mutex_lock(&philo->data->mutex_write);
	gettimeofday(&philo->now, NULL);
	printf("%ld %d is eating\n", philo->now.tv_sec * 1000
		+ philo->now.tv_usec / 1000, philo->id);
	pthread_mutex_unlock(&philo->data->mutex_write);
	philo->last_eat = philo->now;
	philo->nb_eat++;
	if (!m_sleep(philo, philo->data->t_eat))
		return (0);
	pthread_mutex_lock(&philo->left->mutex);
	philo->left->in_use = 0;
	pthread_mutex_unlock(&philo->left->mutex);
	pthread_mutex_lock(&philo->right->mutex);
	philo->right->in_use = 0;
	pthread_mutex_unlock(&philo->right->mutex);
	return (1);
}

int	sleeping(t_philo *philo)
{
	if (someone_died(philo))
		return (0);
	pthread_mutex_lock(&philo->data->mutex_write);
	gettimeofday(&philo->now, NULL);
	printf("%ld %d is sleeping\n", philo->now.tv_sec * 1000
		+ philo->now.tv_usec / 1000, philo->id);
	pthread_mutex_unlock(&philo->data->mutex_write);
	if (!m_sleep(philo, philo->data->t_sleep))
		return (0);
	return (1);
}

int	thinking(t_philo *philo)
{
	if (someone_died(philo))
		return (0);
	pthread_mutex_lock(&philo->data->mutex_write);
	gettimeofday(&philo->now, NULL);
	printf("%ld %d is thinking\n", philo->now.tv_sec * 1000
		+ philo->now.tv_usec / 1000, philo->id);
	pthread_mutex_unlock(&philo->data->mutex_write);
	return (1);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (!take_forks(philo))
			return (NULL);
		if (!eating(philo))
			return (NULL);
		if (!sleeping(philo))
			return (NULL);
		if (!thinking(philo))
			return (NULL);
		if (philo->data->nbr_eat != -1 && philo->nb_eat == philo->data->nbr_eat)
			return (NULL);
	}
	return (NULL);
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
