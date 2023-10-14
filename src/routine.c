/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 16:10:21 by osarsari          #+#    #+#             */
/*   Updated: 2023/10/14 19:51:00 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (check_death(philo))
			return (NULL);
		if (take_forks(philo))
			return (NULL);
		if (check_death(philo))
			return (NULL);
		if (ft_sleep(philo, philo->data->t_sleep))
			return (NULL);
		if (check_death(philo))
			return (NULL);
		if (ft_print(philo, "is thinking\n"))
			return (NULL);
	}
	return (NULL);
}

// Routine
// 1. Think
// 1.1 Check if dead
// 2. Take forks
// 2.1 Check if dead
// 3. Eat
// 3.1 Check if dead
// 4. Sleep
// 4.1 Check if dead
