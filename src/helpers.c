/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 09:02:08 by osarsari          #+#    #+#             */
/*   Updated: 2023/09/18 09:06:27 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	is_int(char *str)
{
	long	num;
	int		i;
	int		sign;

	i = 0;
	num = 0;
	sign = 1;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		num = num * 10 + (str[i] - '0');
		i++;
	}
	num *= sign;
	if (num > 2147483647 || num < -2147483648)
		return (0);
	return (1);
}

int	valid_args(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (!is_int(argv[i]))
			return (0);
		i++;
	}
	return (1);
}
