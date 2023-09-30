/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 22:54:52 by osarsari          #+#    #+#             */
/*   Updated: 2023/09/30 12:24:28 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	dead(t_philo *philo)
{
	struct timeval	now;
	int				time_diff;

	if (feast_over(philo))
		return (1);
	gettimeofday(&now, NULL);
	time_diff = get_time_diff(philo->last_eat, now);
	pthread_mutex_lock(&philo->data->death);
	if (time_diff > philo->data->t_die)
	{
		printf("%li %i died\n", now.tv_sec * 1000 + now.tv_usec / 1000,
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

int	take_forks(t_philo *philo)
{
	struct timeval	now;

	if (dead(philo) || feast_over(philo))
		return (0);
	pthread_mutex_lock(&philo->left->mutex);
	pthread_mutex_lock(&philo->right->mutex);
	gettimeofday(&now, NULL);
	if (philo->left->in_use || philo->right->in_use)
	{
		pthread_mutex_unlock(&philo->left->mutex);
		pthread_mutex_unlock(&philo->right->mutex);
		return (1);
	}
	printf("%li %i has taken a fork\n", now.tv_sec * 1000 + now.tv_usec / 1000,
		philo->id);
	philo->left->in_use = 1;
	philo->right->in_use = 1;
	printf("%li %i has taken a fork\n", now.tv_sec * 1000 + now.tv_usec / 1000,
		philo->id);
	philo->left->philo_id = philo->id;
	philo->right->philo_id = philo->id;
	pthread_mutex_unlock(&philo->left->mutex);
	pthread_mutex_unlock(&philo->right->mutex);
	return (1);
}

int	eat(t_philo *philo)
{
	struct timeval	now;

	if (dead(philo) || feast_over(philo))
		return (0);
	pthread_mutex_lock(&philo->left->mutex);
	pthread_mutex_lock(&philo->right->mutex);
	if (philo->left->philo_id != philo->id || philo->right->philo_id
		!= philo->id)
	{
		pthread_mutex_unlock(&philo->left->mutex);
		pthread_mutex_unlock(&philo->right->mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->left->mutex);
	pthread_mutex_unlock(&philo->right->mutex);
	gettimeofday(&now, NULL);
	printf("%li %i is eating\n", now.tv_sec * 1000 + now.tv_usec / 1000,
		philo->id);
	philo->last_eat = now;
	philo->nb_eat++;
	if (!m_sleep(philo, philo->data->t_eat))
		return (0);
	if (feast_over(philo))
		return (0);
	return (1);
}

int	sleeping(t_philo *philo)
{
	struct timeval	now;

	pthread_mutex_lock(&philo->left->mutex);
	pthread_mutex_lock(&philo->right->mutex);
	philo->left->in_use = 0;
	philo->right->in_use = 0;
	philo->left->philo_id = 0;
	philo->right->philo_id = 0;
	pthread_mutex_unlock(&philo->left->mutex);
	pthread_mutex_unlock(&philo->right->mutex);
	if (dead(philo) || feast_over(philo))
		return (0);
	gettimeofday(&now, NULL);
	printf("%li %i is sleeping\n", now.tv_sec * 1000 + now.tv_usec / 1000,
		philo->id);
	if (!m_sleep(philo, philo->data->t_sleep))
		return (0);
	return (1);
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
		if (!sleeping(philo))
			break ;
		if (!think(philo))
			break ;
	}
	return (NULL);
}
