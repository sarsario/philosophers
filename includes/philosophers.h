/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 08:45:49 by osarsari          #+#    #+#             */
/*   Updated: 2023/09/19 19:12:38 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>

typedef	enum e_state {
	THINKING,
	EATING,
	SLEEPING,
	DEAD
}	t_state;

typedef struct s_fork {
	int				id;
	pthread_mutex_t	use;
}					t_fork;

typedef struct s_data {
	int				nbr;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				nbr_eat;
	int				dead;
	pthread_mutex_t	dead_mutex;
	t_philo			*philo;
}					t_data;

typedef struct s_philo {
	int			id;
	pthread_t	thread;
	t_state		state;
	t_data		*data;
	t_fork		*left;
	t_fork		*right;
	int			last_eat;
	int			nb_eat;
}				t_philo;

int	valid_args(int argc, char **argv);

#endif