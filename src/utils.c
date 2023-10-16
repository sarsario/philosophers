/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 09:02:08 by osarsari          #+#    #+#             */
/*   Updated: 2023/10/16 13:33:52 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	is_pos(char *str)
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
		argc--;
		if (!is_pos(argv[argc]))
			return (0);
	}
	if (!ft_atoi(argv[1]) || !ft_atoi(argv[2]))
		return (0);
	if (argc == 6 && !ft_atoi(argv[5]))
		return (0);
	return (1);
}

int	ft_atoi(char *str)
{
	int		i;
	long	nbr;

	i = -1;
	nbr = 0;
	while (str[++i])
		nbr = nbr * 10 + (str[i] - '0');
	return (nbr);
}

static int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int	ft_perror(char *str)
{
	write(2, str, ft_strlen(str));
	return (1);
}
