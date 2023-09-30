/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 08:53:31 by osarsari          #+#    #+#             */
/*   Updated: 2023/09/30 12:16:31 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	alloc_error(t_data *data, t_philo *philo)
{
	if (data)
	{
		if (data->forks)
			free(data->forks);
		pthread_mutex_destroy(&data->death);
		pthread_mutex_destroy(&data->full);
		free(data);
	}
	if (philo)
		free(philo);
	return (ft_perror("Error: allocation failed\n"));
}

static t_fork	*alloc_forks(int nbr)
{
	t_fork	*forks;
	int		i;

	forks = malloc(sizeof(t_fork) * nbr);
	if (!forks)
		return (NULL);
	i = -1;
	while (++i < nbr)
	{
		forks[i].id = i + 1;
		forks[i].in_use = 0;
		forks[i].philo_id = 0;
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
	}
	return (forks);
}

static int	set_data(t_data *data, int argc, char **argv)
{
	data->nbr = ft_atoi(argv[1]);
	data->t_die = ft_atoi(argv[2]);
	data->t_eat = ft_atoi(argv[3]);
	data->t_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		data->nbr_eat = ft_atoi(argv[5]);
		data->nbr_full = malloc(sizeof(int) * data->nbr);
		if (!data->nbr_full)
			return (0);
	}
	else
	{
		data->nbr_eat = -1;
		data->nbr_full = 0;
	}
	data->dead = 0;
	return (1);
}

t_data	*alloc_data(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data || !set_data(data, argc, argv))
		return (NULL);
	if (pthread_mutex_init(&data->death, NULL))
		return (free_data(data));
	if (pthread_mutex_init(&data->full, NULL))
	{
		pthread_mutex_destroy(&data->death);
		return (free_data(data));
	}
	data->forks = alloc_forks(data->nbr);
	if (!data->forks)
	{
		pthread_mutex_destroy(&data->death);
		pthread_mutex_destroy(&data->full);
		return (free_data(data));
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
	while (i < data->nbr)
	{
		philo[i].id = i + 1;
		philo[i].nb_eat = 0;
		philo[i].data = data;
		philo[i].left = &data->forks[i];
		philo[i].right = &data->forks[(i + 1) % data->nbr];
		i++;
	}
	return (philo);
}
