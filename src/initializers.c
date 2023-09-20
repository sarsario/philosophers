/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 08:53:31 by osarsari          #+#    #+#             */
/*   Updated: 2023/09/20 17:03:31 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	init_data(t_data *data, int argc, char **argv)
{
	data->nbr = ft_atoi(argv[1]);
	data->t_die = ft_atoi(argv[2]);
	data->t_eat = ft_atoi(argv[3]);
	data->t_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->nbr_eat = ft_atoi(argv[5]);
	else
		data->nbr_eat = -1;
	pthread_mutex_init(&data->dead_mutex, NULL);
}

t_philo	*init_philo(t_data *data)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = (t_philo *)malloc(sizeof(t_philo) * data->nbr);
	if (!philo)
		return (NULL);
	while (i < data->nbr)
	{
		philo[i].id = i + 1;
		philo[i].state = SLEEPING;
		philo[i].nb_eat = 0;
		philo[i].data = data;
		i++;
	}
	return (philo);
}

t_fork	*init_forks(t_data *data)
{
	t_fork	*forks;
	int		i;

	i = 0;
	forks = (t_fork *)malloc(sizeof(t_fork) * data->nbr);
	if (!forks)
		return (NULL);
	while (i < data->nbr)
	{
		forks[i].id = i + 1;
		pthread_mutex_init(&forks[i].use, NULL);
		i++;
	}
	return (forks);
}
