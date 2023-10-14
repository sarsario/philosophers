/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 15:54:52 by osarsari          #+#    #+#             */
/*   Updated: 2023/10/14 19:46:13 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	init_philo(t_philo *philo, int id)
{
	philo->id = id;
	philo->eaten = 0;
	philo->slept = 0;
	philo->nb_eat = 0;
}

t_philo	*alloc_single_philo(t_data *data, int id)
{
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	init_philo(philo, id);
	philo->data = data;
	philo->left = &data->forks[0];
	philo->right = NULL;
	return (philo);
}

int	check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex);
	if (philo->data->dead)
	{
		pthread_mutex_unlock(&philo->data->mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->mutex);
	return (0);
}
