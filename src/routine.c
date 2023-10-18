/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:02:44 by osarsari          #+#    #+#             */
/*   Updated: 2023/10/18 15:49:10 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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
