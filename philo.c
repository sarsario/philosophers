/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 08:50:38 by osarsari          #+#    #+#             */
/*   Updated: 2023/09/19 19:22:36 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philosophers.h"

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philo;

	if (argc < 5 || argc > 6)
		return (1);
	if (!valid_args(argc, argv))
		return (1);
	data.nbr = ft_atoi(argv[1]);
	data.t_die = ft_atoi(argv[2]);
	data.t_eat = ft_atoi(argv[3]);
	data.t_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data.nbr_eat = ft_atoi(argv[5]);
	else
		data.nbr_eat = -1;
	philo = malloc(sizeof(t_philo) * data.nbr);
	// if (!philo)
	// 	return (1);
	// if (!init_philo(philo, &data))
	// 	return (1);
	// if (!start_threads(philo, &data))
	// 	return (1);
	return (0);
}
