/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:02:44 by osarsari          #+#    #+#             */
/*   Updated: 2023/10/17 12:49:44 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	hmdl(t_philo *philo)
{
	philo->nb_eat++;
	philo->slept = 0;
	philo->ate = 1;
	if (philo->data->nbr_eat == -1)
		return ;
	pthread_mutex_lock(&philo->data->mutex_write);
	philo->data->eat_table[philo->id - 1] = philo->nb_eat;
	pthread_mutex_unlock(&philo->data->mutex_write);
}

int	eating(t_philo *philo)
{
	if (self_death(philo))
		return (0);
	if (philo->ate)
		return (1);
	if (!have_two_forks(philo))
		return (1);
	pthread_mutex_lock(&philo->data->mutex_write);
	gettimeofday(&philo->now, NULL);
	printf("%ld %d is eating\n", philo->now.tv_sec * 1000 + \
		philo->now.tv_usec / 1000, philo->id);
	pthread_mutex_unlock(&philo->data->mutex_write);
	philo->last_eat = philo->now;
	if (!m_sleep(philo, philo->data->t_eat))
	{
		release_forks(philo);
		return (0);
	}
	hmdl(philo);
	release_forks(philo);
	return (1);
}

int	sleeping(t_philo *philo)
{
	if (self_death(philo))
		return (0);
	if (philo->slept)
		return (1);
	pthread_mutex_lock(&philo->data->mutex_write);
	gettimeofday(&philo->now, NULL);
	printf("%ld %d is sleeping\n", philo->now.tv_sec * 1000 + \
		philo->now.tv_usec / 1000, philo->id);
	pthread_mutex_unlock(&philo->data->mutex_write);
	philo->thinking = 0;
	if (!m_sleep(philo, philo->data->t_sleep))
		return (0);
	philo->slept = 1;
	philo->thinking = 0;
	return (1);
}

int	thinking(t_philo *philo)
{
	if (self_death(philo))
		return (0);
	if (!philo->thinking)
	{
		philo->thinking = 1;
		philo->ate = 0;
		pthread_mutex_lock(&philo->data->mutex_write);
		gettimeofday(&philo->now, NULL);
		printf("%ld %d is thinking\n", philo->now.tv_sec * 1000 + \
			philo->now.tv_usec / 1000, philo->id);
		pthread_mutex_unlock(&philo->data->mutex_write);
	}
	return (1);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (!no_food(philo) && grab_forks(philo))
			if (!eating(philo))
				break ;
		if (no_food(philo) || !sleeping(philo))
			break ;
		if (no_food(philo) || !thinking(philo))
			break ;
	}
	return (NULL);
}
