/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 15:54:52 by osarsari          #+#    #+#             */
/*   Updated: 2023/09/30 11:22:58 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

t_philo	*alloc_single_philo(t_data *data)
{
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->id = 1;
	philo->data = data;
	philo->nb_eat = 0;
	philo->last_eat.tv_sec = 0;
	philo->last_eat.tv_usec = 0;
	philo->left = &data->forks[0];
	philo->right = NULL;
	return (philo);
}

int	check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death);
	if (philo->data->dead)
	{
		pthread_mutex_unlock(&philo->data->death);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->death);
	return (0);
}
