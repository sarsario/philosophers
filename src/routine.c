/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:02:44 by osarsari          #+#    #+#             */
/*   Updated: 2023/10/18 15:21:27 by osarsari         ###   ########.fr       */
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

int	altruism(t_philo *philo)
{
	struct timeval	own_time;
	struct timeval	right_neighbor_time;
	struct timeval	left_neighbor_time;

	pthread_mutex_lock(&philo->data->mutex_write);
	own_time = philo->last_eat;
	if (philo->id == philo->data->nbr)
		right_neighbor_time = philo->data->last_eat[0];
	else
		right_neighbor_time = philo->data->last_eat[philo->id];
	if (philo->id == 1)
		left_neighbor_time = philo->data->last_eat[philo->data->nbr - 1];
	else
		left_neighbor_time = philo->data->last_eat[philo->id - 2];
	if (own_time.tv_sec * 1000 + own_time.tv_usec / 1000 > \
		right_neighbor_time.tv_sec * 1000 + right_neighbor_time.tv_usec / 1000 \
		|| own_time.tv_sec * 1000 + own_time.tv_usec / 1000 > \
		left_neighbor_time.tv_sec * 1000 + left_neighbor_time.tv_usec / 1000)
	{
		pthread_mutex_unlock(&philo->data->mutex_write);
			return (1);
	}
	pthread_mutex_unlock(&philo->data->mutex_write);
	return (0);
}

int	grab_forks(t_philo *philo)
{
	if (altruism(philo))
		return (0);
	pthread_mutex_lock(&philo->left->mutex);
	pthread_mutex_lock(&philo->right->mutex);
	if (philo->left->used_by != 0 || philo->right->used_by != 0)
	{
		pthread_mutex_unlock(&philo->left->mutex);
		pthread_mutex_unlock(&philo->right->mutex);
		return (0);
	}
	philo->left->used_by = philo->id;
	philo->right->used_by = philo->id;
	pthread_mutex_unlock(&philo->left->mutex);
	pthread_mutex_unlock(&philo->right->mutex);
	if (!try_print(philo, "has taken a fork")
		|| !try_print(philo, "has taken a fork"))
		return (0);
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

	if (philo->data->nbr_eat == -1)
		return (0);
	pthread_mutex_lock(&philo->data->mutex_write);
	i = 0;
	j = 0;
	while (i < philo->data->nbr)
	{
		if (philo->data->eat_table[i] >= philo->data->nbr_eat)
			j++;
		i++;
	}
	if (j == philo->data->nbr)
	{
		pthread_mutex_unlock(&philo->data->mutex_write);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->mutex_write);
	return (0);
}

void	update_last_eat(t_philo *philo)
{
	philo->ate = 1;
	philo->slept = 0;
	philo->nb_eat++;
	pthread_mutex_lock(&philo->data->mutex_write);
	philo->last_eat = philo->now;
	philo->data->last_eat[philo->id - 1] = philo->last_eat;
	pthread_mutex_unlock(&philo->data->mutex_write);
}

int	eating(t_philo *philo)
{
	if (!philo || self_death(philo) || no_food(philo))
		return (0);
	if (philo->ate || !grab_forks(philo))
		return (1);
	if (!try_print(philo, "is eating"))
	{
		release_forks(philo);
		return (0);
	}
	update_last_eat(philo);
	if (!m_sleep(philo, philo->data->t_eat))
	{
		release_forks(philo);
		return (0);
	}
	pthread_mutex_lock(&philo->data->mutex_write);
	if (philo->data->nbr_eat != -1)
		philo->data->eat_table[philo->id - 1] = philo->nb_eat;
	pthread_mutex_unlock(&philo->data->mutex_write);
	release_forks(philo);
	return (1);
}

int	sleeping(t_philo *philo)
{
	if (!philo || self_death(philo) || no_food(philo))
		return (0);
	if (philo->slept || !philo->ate)
		return (1);
	if (!try_print(philo, "is sleeping"))
		return (0);
	if (!m_sleep(philo, philo->data->t_sleep))
		return (0);
	philo->slept = 1;
	philo->thinking = 0;
	return (1);
}

int	thinking(t_philo *philo)
{
	if (!philo || self_death(philo) || no_food(philo))
		return (0);
	if (!philo->thinking && philo->slept)
	{
		philo->thinking = 1;
		philo->ate = 0;
		if (!try_print(philo, "is thinking"))
			return (0);
	}
	return (1);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (!eating(philo))
			break ;
		if (!sleeping(philo))
			break ;
		if (!thinking(philo))
			break ;
	}
	return (NULL);
}
