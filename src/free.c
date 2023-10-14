/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 14:22:23 by osarsari          #+#    #+#             */
/*   Updated: 2023/09/24 14:42:10 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	deep_free(t_philo *philo)
{
	int	i;

	if (!philo)
		return ;
	if (philo->data)
	{
		if (philo->data->forks)
		{
			i = 0;
			while (i < philo->data->nbr)
				pthread_mutex_destroy(&philo->data->forks[i++].mutex);
			free(philo->data->forks);
		}
		pthread_mutex_destroy(&philo->data->mutex);
		free(philo->data);
	}
	free(philo);
}