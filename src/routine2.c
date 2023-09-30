/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 10:56:36 by osarsari          #+#    #+#             */
/*   Updated: 2023/09/30 12:39:48 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	get_time_diff(struct timeval start, struct timeval end)
{
	return ((end.tv_sec * 1000 + end.tv_usec / 1000) - (start.tv_sec * 1000
			+ start.tv_usec / 1000));
}

int	feast_over(t_philo *philo)
{
	int	i;

	i = 0;
	if (philo->data->nbr_eat != -1 && philo->nb_eat >= philo->data->nbr_eat)
	{
		pthread_mutex_lock(&philo->data->full);
		philo->data->nbr_full[philo->id - 1] = 1;
		while (i < philo->data->nbr)
		{
			if (philo->data->nbr_full[i] == 0)
				break ;
			i++;
		}
		if (i == philo->data->nbr)
		{
			pthread_mutex_unlock(&philo->data->full);
			return (1);
		}
		pthread_mutex_unlock(&philo->data->full);
	}
	return (0);
}

int	think(t_philo *philo)
{
	struct timeval	now;
	int				stop_thinking;

	if (dead(philo) || feast_over(philo))
		return (0);
	gettimeofday(&now, NULL);
	printf("%li %i is thinking\n", now.tv_sec * 1000 + now.tv_usec / 1000,
		philo->id);
	stop_thinking = 0;
	while (!stop_thinking)
	{
		pthread_mutex_lock(&philo->left->mutex);
		pthread_mutex_lock(&philo->right->mutex);
		if (!philo->left->in_use && !philo->right->in_use)
			stop_thinking = 1;
		pthread_mutex_unlock(&philo->left->mutex);
		pthread_mutex_unlock(&philo->right->mutex);
		if (!m_sleep(philo, 1))
			return (0);
	}
	return (1);
}
