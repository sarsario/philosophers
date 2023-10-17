/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 13:29:33 by osarsari          #+#    #+#             */
/*   Updated: 2023/10/17 14:08:28 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	assign(t_data *data, int argc, char **argv)
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
	data->last_eat = NULL;
	data->eat_table = NULL;
	data->forks = NULL;
}

static int	alloc_eat_table(t_data *data)
{
	int	i;

	i = 0;
	if (data->nbr_eat != -1)
	{
		data->eat_table = malloc(sizeof(int) * data->nbr);
		if (!data->eat_table)
			return (0);
		while (i < data->nbr)
		{
			data->eat_table[i] = 0;
			i++;
		}
	}
	return (1);
}

static int	init_data_mutex(t_data *data)
{
	if (pthread_mutex_init(&data->mutex_dead, NULL))
		return (0);
	if (pthread_mutex_init(&data->mutex_write, NULL))
	{
		pthread_mutex_destroy(&data->mutex_dead);
		return (0);
	}
	return (1);
}

static int	alloc_forks(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(t_fork) * data->nbr);
	if (!data->forks)
		return (0);
	while (i < data->nbr)
	{
		data->forks[i].id = i + 1;
		data->forks[i].used_by = 0;
		if (pthread_mutex_init(&data->forks[i].mutex, NULL) != 0)
		{
			while (i > 0)
				pthread_mutex_destroy(&data->forks[--i].mutex);
			free(data->forks);
			return (0);
		}
		i++;
	}
	return (1);
}

t_data	*set_data(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	if (!init_data_mutex(data))
		return (free(data), NULL);
	assign(data, argc, argv);
	data->last_eat = malloc(sizeof(struct timeval) * data->nbr);
	if (!data->last_eat)
		return (free_data(data));
	if (!alloc_eat_table(data))
		return (free_data(data));
	if (!alloc_forks(data))
		return (free_data(data));
	return (data);
}
