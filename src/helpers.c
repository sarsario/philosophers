/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 09:02:08 by osarsari          #+#    #+#             */
/*   Updated: 2023/09/19 16:14:18 by osarsari         ###   ########.fr       */
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
