/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 13:55:44 by osarsari          #+#    #+#             */
/*   Updated: 2023/10/18 15:51:03 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	free_forks(t_fork *forks)
{
	int	i;

	if (!forks)
		return ;
	i = 0;
	while (forks[i].id != -1)
	{
		pthread_mutex_destroy(&forks[i].mutex);
		i++;
	}
	free(forks);
}

t_data	*free_data(t_data *data)
{
	if (data && data->last_eat)
		free(data->last_eat);
	if (data && data->eat_table)
		free(data->eat_table);
	if (data && data->forks)
		free(data->forks);
	pthread_mutex_destroy(&data->mutex_dead);
	pthread_mutex_destroy(&data->mutex_write);
	if (data)
		free(data);
	return (NULL);
}

t_data	*free_data_without_destroy(t_data *data)
{
	if (data && data->last_eat)
		free(data->last_eat);
	if (data && data->eat_table)
		free(data->eat_table);
	if (data && data->forks)
		free(data->forks);
	if (data)
		free(data);
	return (NULL);
}
