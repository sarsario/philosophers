/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 20:32:12 by osarsari          #+#    #+#             */
/*   Updated: 2023/09/30 23:08:41 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_data	*init_data(int argc, char **argv)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->n = ft_atoi(argv[1]);
	data->ttd = ft_atoi(argv[2]);
	data->tte = ft_atoi(argv[3]);
	data->tts = ft_atoi(argv[4]);
	if (argc == 6)
		data->nme = ft_atoi(argv[5]);
	else
		data->nme = -1;
	data->dead = 0;
	data->write = 0;
	data->start = 0;
	data->eat_count = 0;
	data->m_dead = 0;
	data->m_eat = 0;
	data->m_write = 0;
	return (data);
}

void	*free_data(t_data *data)
{
	if (data)
	{
		if (data->eat_count)
			free(data->eat_count);
		if (data->m_eat)
			free(data->m_eat);
		if (data->m_dead)
			free(data->m_dead);
		if (data->m_write)
			free(data->m_write);
		free(data);
	}
	return (NULL);
}

t_data	*malloc_data(t_data *data)
{
	data->eat_count = malloc(sizeof(int) * data->n);
	data->m_eat = malloc(sizeof(pthread_mutex_t));
	data->m_dead = malloc(sizeof(pthread_mutex_t));
	data->m_write = malloc(sizeof(pthread_mutex_t));
	if (!data->eat_count || !data->m_eat || !data->m_dead || !data->m_write)
		return (free_data(data));
	return (data);
}

t_fork	*init_forks(t_data *data)
{
	int		i;
	t_fork	*forks;

	i = 0;
	forks = malloc(sizeof(t_fork) * data->n);
	if (!forks)
		return (NULL);
	while (i < data->n)
	{
		forks[i].id = i + 1;
		forks[i].available = 1;
		if (pthread_mutex_init(&forks[i].mutex, NULL) != 0)
		{
			while (i > 0)
				pthread_mutex_destroy(&forks[i--].mutex);
			free(forks);
			return (NULL);
		}
		i++;
	}
	return (forks);
}

t_philo	*init_philo(t_data *data, t_fork *forks)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = malloc(sizeof(t_philo) * data->n);
	if (!philo)
		return (NULL);
	while (i < data->n)
	{
		philo[i].id = i + 1;
		philo[i].data = data;
		philo[i].last_eat = 0;
		philo[i].left = &forks[i];
		if (i == data->n - 1)
			philo[i].right = &forks[0];
		else
			philo[i].right = &forks[i + 1];
		i++;
	}
	return (philo);
}
