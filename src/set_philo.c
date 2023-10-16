/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:16:57 by osarsari          #+#    #+#             */
/*   Updated: 2023/10/16 14:21:29 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_philo	*set_philo(t_data *data)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = malloc(sizeof(t_philo) * data->nbr);
	if (!philo)
		return (NULL);
	while (i < data->nbr)
	{
		philo[i].id = i + 1;
		philo[i].data = data;
		philo[i].thinking = 0;
		philo[i].nb_eat = 0;
		philo[i].left = &data->forks[i];
		if (i == data->nbr - 1)
			philo[i].right = &data->forks[0];
		else
			philo[i].right = &data->forks[i + 1];
		i++;
	}
	return (philo);
}
