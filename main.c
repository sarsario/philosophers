/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 08:50:38 by osarsari          #+#    #+#             */
/*   Updated: 2023/09/18 09:01:38 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philosophers.h"

int	main(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (0);
	if (!valid_args(argv))
		return (0);
	return (0);
}
