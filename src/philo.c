/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 08:50:38 by osarsari          #+#    #+#             */
/*   Updated: 2023/09/20 18:02:06 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philo;
	t_fork	*forks;

	if (argc < 5 || argc > 6)
		return (1);
	if (!valid_args(argc, argv))
		return (1);
	init_data(&data, argc, argv);
	philo = init_philo(&data);
	forks = init_forks(&data);
	if (failed_malloc(&data, philo, forks))
		return (destroy_mutexes(&data, forks));
	destroy_mutexes(&data, forks);
	return (0);
}
