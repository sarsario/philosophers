/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 08:53:31 by osarsari          #+#    #+#             */
/*   Updated: 2023/10/14 19:46:20 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static t_fork	*alloc_forks(int nbr)
{
	t_fork	*forks;
	int		i;

	forks = malloc(sizeof(t_fork) * nbr);
	if (!forks)
		return (NULL);
	i = 0;
	while (i < nbr)
	{
		forks[i].id = i + 1;
		forks[i].in_use = 0;
		if (pthread_mutex_init(&forks[i].mutex, NULL))
		{
			while (i >= 0)
			{
				pthread_mutex_destroy(&forks[i].mutex);
				i--;
			}
			free(forks);
			return (NULL);
		}
		forks[i].in_use = 0;
		i++;
	}
	return (forks);
}

static void	set_data(t_data *data, int argc, char **argv)
{
	data->nbr = ft_atoi(argv[1]);
	data->t_die = ft_atoi(argv[2]);
	data->t_eat = ft_atoi(argv[3]);
	data->t_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->nbr_eat = ft_atoi(argv[5]);
	else
		data->nbr_eat = -1;
	data->dead = 0;
}

t_data	*alloc_data(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	set_data(data, argc, argv);
	if (pthread_mutex_init(&data->mutex_dead, NULL))
		return (free(data), NULL);
	if (pthread_mutex_init(&data->mutex_write, NULL))
	{
		pthread_mutex_destroy(&data->mutex_dead);
		return (free(data), NULL);
	}
	data->forks = alloc_forks(data->nbr);
	if (!data->forks)
	{
		pthread_mutex_destroy(&data->mutex_dead);
		pthread_mutex_destroy(&data->mutex_write);
		free(data);
		return (NULL);
	}
	return (data);
}

t_philo	*alloc_philo(t_data *data)
{
	t_philo	*philo;
	int		i;

	if (!data)
		return (NULL);
	philo = malloc(sizeof(t_philo) * data->nbr);
	if (!philo)
		return (NULL);
	i = 0;
	if (data->nbr == 1)
		return (alloc_single_philo(data, i + 1));
	while (i < data->nbr)
	{
		init_philo(&philo[i], i + 1);
		philo[i].data = data;
		philo[i].left = &data->forks[i];
		philo[i].right = &data->forks[(i + 1) % data->nbr];
		i++;
	}
	return (philo);
}