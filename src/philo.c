/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 08:50:38 by osarsari          #+#    #+#             */
/*   Updated: 2023/10/14 19:27:47 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char **argv)
{
	t_data	*data;
	t_philo	*philo;

	if (argc < 5 || argc > 6)
		return (ft_perror("Error: wrong number of arguments\n"));
	if (!valid_args(argc, argv))
		return (ft_perror("Error: invalid arguments\n"));
	data = alloc_data(argc, argv);
	if (!data)
		return (alloc_error(NULL, NULL));
	philo = alloc_philo(data);
	if (!philo)
		return (alloc_error(data, philo));
	if (!start_threads(philo))
		return (start_error(philo));
	if (!join_threads(philo))
		return (join_error(philo));
	deep_free(philo);
	return (0);
}
