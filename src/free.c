/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 14:22:23 by osarsari          #+#    #+#             */
/*   Updated: 2023/10/14 19:44:27 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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

int	alloc_error(t_data *data, t_philo *philo)
{
	if (data)
	{
		if (data->forks)
			free(data->forks);
		pthread_mutex_destroy(&data->mutex);
		free(data);
	}
	if (philo)
		free(philo);
	return (ft_perror("Error: allocation failed\n"));
}
