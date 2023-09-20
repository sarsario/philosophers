/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 09:02:08 by osarsari          #+#    #+#             */
/*   Updated: 2023/09/20 18:00:36 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	is_pos(char *str)
{
	int		i;
	long	nbr;

	i = 0;
	nbr = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		nbr = nbr * 10 + (str[i] - '0');
		if (nbr > 2147483647)
			return (0);
		i++;
	}
	return (1);
}

int	valid_args(int argc, char **argv)
{
	while (argc > 1)
	{
		if (!is_pos(argv[argc - 1]))
			return (0);
		argc--;
	}
	return (1);
}

int	failed_malloc(t_data *data, t_philo *philo, t_fork *forks)
{
	int	i;

	if (!philo || !forks)
	{
		if (philo)
			free(philo);
		if (forks)
		{
			i = 0;
			while (i < data->nbr)
				pthread_mutex_destroy(&forks[i++].use);
		}
		return (1);
	}
	return (0);
}

int	destroy_mutex(t_data *data, t_fork *forks)
{
	int	i;

	pthread_mutex_destroy(&data->dead_mutex);
	if (forks)
	{
		i = 0;
		while (i < data->nbr)
			pthread_mutex_destroy(&forks[i++].use);
	}
	return (1);
}
