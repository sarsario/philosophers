/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 08:45:49 by osarsari          #+#    #+#             */
/*   Updated: 2023/09/23 14:36:44 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_fork {
	int				id;
	pthread_mutex_t	mutex;
}					t_fork;

typedef struct s_data {
	int				nbr;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				nbr_eat;
	int				dead;
	pthread_mutex_t	mutex;
	t_fork			*forks;
}					t_data;

typedef struct s_philo {
	int				id;
	pthread_t		thread;
	struct timeval	last_eat;
	int				nb_eat;
	t_data			*data;
	t_fork			*left;
	t_fork			*right;
}				t_philo;

int		ft_atoi(char *str);
int		ft_perror(char *str);
int		valid_args(int argc, char **argv);
int		alloc_error(t_data *data, t_philo *philo);
t_data	*alloc_data(int argc, char **argv);
t_philo	*alloc_philo(t_data *data);

#endif