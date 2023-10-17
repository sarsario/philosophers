/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:16:57 by osarsari          #+#    #+#             */
/*   Updated: 2023/10/17 12:13:05 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	init_philo(t_philo *philo, t_data *data, int i)
{
	philo->id = i + 1;
	philo->data = data;
	philo->nb_eat = 0;
	philo->ate = 0;
	philo->slept = 0;
	philo->thinking = 0;
	philo->left = &data->forks[i];
	if (i == data->nbr - 1)
		philo->right = &data->forks[0];
	else
		philo->right = &data->forks[i + 1];
}

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
		init_philo(&philo[i], data, i);
		i++;
	}
	return (philo);
}
