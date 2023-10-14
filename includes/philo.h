/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 08:45:49 by osarsari          #+#    #+#             */
/*   Updated: 2023/10/14 19:45:08 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_fork {
	int				id;
	int				in_use;
	pthread_mutex_t	mutex;
}					t_fork;

typedef struct s_data {
	int				nbr;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				nbr_eat;
	int				dead;
	struct timeval	start;
	pthread_mutex_t	mutex_dead;
	pthread_mutex_t	mutex_write;
	t_fork			*forks;
}					t_data;

typedef struct s_philo {
	int				id;
	pthread_t		thread;
	struct timeval	last_eat;
	int				eaten;
	int				slept;
	int				nb_eat;
	t_data			*data;
	t_fork			*left;
	t_fork			*right;
}					t_philo;

int		ft_atoi(char *str);
int		ft_sleep(t_philo *philo, int duration);
int		ft_perror(char *str);
int		valid_args(int argc, char **argv);
void	init_philo(t_philo *philo, int id);
int		alloc_error(t_data *data, t_philo *philo);
t_data	*alloc_data(int argc, char **argv);
t_philo	*alloc_single_philo(t_data *data, int id);
t_philo	*alloc_philo(t_data *data);
void	*routine(void *arg);
int		start_threads(t_philo *philo);
int		join_threads(t_philo *philo);
void	deep_free(t_philo *philo);
int		start_error(t_philo *philo);
int		join_error(t_philo *philo);
int		check_death(t_philo *philo);
int		m_sleep(t_philo *philo, int ms);

#endif