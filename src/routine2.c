/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 16:23:27 by osarsari          #+#    #+#             */
/*   Updated: 2023/10/16 16:57:50 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	self_death(t_philo *philo)
{
	gettimeofday(&philo->now, NULL);
	if (time_diff(&philo->last_eat, &philo->now) > philo->data->t_die)
	{
		pthread_mutex_lock(&philo->data->mutex_dead);
		if (!philo->data->dead)
		{
			philo->data->dead = 1;
			pthread_mutex_lock(&philo->data->mutex_write);
			printf("%ld %d died\n", philo->now.tv_sec * 1000 + \
				philo->now.tv_usec / 1000, philo->id);
			pthread_mutex_unlock(&philo->data->mutex_write);
		}
		pthread_mutex_unlock(&philo->data->mutex_dead);
		return (1);
	}
	return (0);
}

int	have_two_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->left->mutex);
	if (philo->left->used_by != philo->id)
	{
		pthread_mutex_unlock(&philo->left->mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->left->mutex);
	pthread_mutex_lock(&philo->right->mutex);
	if (philo->right->used_by != philo->id)
	{
		pthread_mutex_unlock(&philo->right->mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->right->mutex);
	return (1);
}

int	grab_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->left->mutex);
	if (philo->left->used_by)
	{
		pthread_mutex_unlock(&philo->left->mutex);
		return (0);
	}
	philo->left->used_by = philo->id;
	pthread_mutex_unlock(&philo->left->mutex);
	pthread_mutex_lock(&philo->right->mutex);
	if (philo->right->used_by)
	{
		pthread_mutex_unlock(&philo->right->mutex);
		return (0);
	}
	philo->right->used_by = philo->id;
	pthread_mutex_unlock(&philo->right->mutex);
	return (1);
}

void	release_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->left->mutex);
	philo->left->used_by = 0;
	pthread_mutex_unlock(&philo->left->mutex);
	pthread_mutex_lock(&philo->right->mutex);
	philo->right->used_by = 0;
	pthread_mutex_unlock(&philo->right->mutex);
}

int	no_food(t_philo *philo)
{
	int	i;
	int	j;

	pthread_mutex_lock(&philo->data->mutex_write);
	i = 0;
	j = 0;
	while (i < philo->data->nbr)
	{
		if (philo->data->eat_table[i] >= philo->data->nbr_eat)
			j++;
		i++;
	}
	pthread_mutex_unlock(&philo->data->mutex_write);
	return (j == philo->data->nbr);
}
