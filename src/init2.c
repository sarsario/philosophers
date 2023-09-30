/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 15:54:52 by osarsari          #+#    #+#             */
/*   Updated: 2023/09/30 12:21:52 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	died_of_loneliness(t_data *data)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	printf("%li 1 has taken a fork\n", now.tv_sec * 1000 + now.tv_usec / 1000);
	usleep(data->t_die * 1000);
	gettimeofday(&now, NULL);
	printf("%li 1 died\n", now.tv_sec * 1000 + now.tv_usec / 1000);
	free_data(data);
	return (0);
}

t_data	*free_data(t_data *data)
{
	free(data->nbr_full);
	free(data);
	return (NULL);
}
