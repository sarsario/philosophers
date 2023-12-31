/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 08:45:49 by osarsari          #+#    #+#             */
/*   Updated: 2023/10/18 15:50:23 by osarsari         ###   ########.fr       */
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
	int				used_by;
	pthread_mutex_t	mutex;
}					t_fork;

typedef struct s_data {
	int				nbr;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				nbr_eat;
	struct timeval	*last_eat;
	int				*eat_table;
	int				dead;
	pthread_mutex_t	mutex_dead;
	pthread_mutex_t	mutex_write;
	t_fork			*forks;
}					t_data;

typedef struct s_philo {
	int				id;
	pthread_t		thread;
	struct timeval	last_eat;
	struct timeval	now;
	struct timeval	start;
	int				thinking;
	int				slept;
	int				ate;
	int				nb_eat;
	t_data			*data;
	t_fork			*left;
	t_fork			*right;
}					t_philo;

int		ft_atoi(char *str);
int		ft_perror(char *str);
int		valid_args(int argc, char **argv);
void	free_forks(t_fork *forks);
t_data	*free_data(t_data *data);
t_data	*free_data_without_destroy(t_data *data);
t_data	*set_data(int argc, char **argv);
t_philo	*set_philo(t_data *data);
int		time_diff(struct timeval *start, struct timeval *now);
int		m_sleep(t_philo *philo, int time);
int		try_print(t_philo *philo, char *msg);
int		single_philo(t_philo *philo);
int		force_death(t_philo *philo);
int		self_death(t_philo *philo);
int		altruism(t_philo *philo);
int		grab_forks(t_philo *philo);
void	release_forks(t_philo *philo);
int		no_food(t_philo *philo);
void	*routine(void *arg);
int		start_thread(t_philo *philo);
int		join_thread(t_philo *philo);

#endif