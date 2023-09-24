/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 15:54:52 by osarsari          #+#    #+#             */
/*   Updated: 2023/09/24 18:38:33 by osarsari         ###   ########.fr       */
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
	philo->left = &data->forks[0];
	philo->right = NULL;
	return (philo);
}

int	check_death(t_philo *philo)
{
	printf("%d goes to cemetery\n", philo->id);
	pthread_mutex_lock(&philo->data->mutex);
	printf("%d looks for a friend\n", philo->id);
	if (philo->data->dead)
	{
		printf("%d mourns the death of a friend\n", philo->id);
		pthread_mutex_unlock(&philo->data->mutex);
		return (1);
	}
	printf("%d cemetery is empty\n", philo->id);
	pthread_mutex_unlock(&philo->data->mutex);
	return (0);
}
