/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 23:17:55 by osarsari          #+#    #+#             */
/*   Updated: 2023/09/30 23:59:19 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// Infinite loop
// - Lock left fork
// - Lock right fork
//
// Break if:
// - Philo is dead
void	*routine(t_philo *philo, t_fork *forks)
{
	while (1)
	{
		eat(philo, forks);
		sleep(philo);
	}
	return (NULL);
}