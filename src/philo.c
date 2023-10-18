/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 08:50:38 by osarsari          #+#    #+#             */
/*   Updated: 2023/10/18 19:43:03 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	run_thread(t_philo *philo, t_data *data)
{
	if (!start_thread(philo))
	{
		free_data(data);
		free(philo);
		return (ft_perror("Error: thread creation failed\n"));
	}
	if (!join_thread(philo))
	{
		free_data(data);
		free(philo);
		return (ft_perror("Error: thread join failed\n"));
	}
	free_data(data);
	free(philo);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;
	t_philo	*philo;

	if (argc < 5 || argc > 6)
		return (ft_perror("Error: wrong number of arguments\n"));
	if (!valid_args(argc, argv))
		return (ft_perror("Error: invalid arguments\n"));
	data = set_data(argc, argv);
	if (!data)
		return (ft_perror("Error: malloc failed\n"));
	philo = set_philo(data);
	if (!philo)
	{
		free_data(data);
		return (ft_perror("Error: malloc failed\n"));
	}
	if (philo->data->nbr == 1)
		return (single_philo(philo));
	return (run_thread(philo, data));
}
