/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 08:45:49 by osarsari          #+#    #+#             */
/*   Updated: 2023/09/30 23:41:24 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

typedef struct s_fork
{
	int				id;
	int				available;
	pthread_mutex_t	mutex;
}					t_fork;

typedef struct s_data
{
	int				n;
	int				ttd;
	int				tte;
	int				tts;
	int				nme;
	int				*eat_count;
	int				dead;
	int				start;
	int				write;
	pthread_mutex_t	*m_eat;
	pthread_mutex_t	*m_dead;
	pthread_mutex_t	*m_write;
}					t_data;

typedef struct s_philo
{
	int				id;
	int				last_eat;
	int				slept;
	t_data			*data;
	t_fork			*left;
	t_fork			*right;
	pthread_t		thread;
}					t_philo;

int					ft_strlen(char *str);
int					ft_isdigit(char c);
int					ft_atoi(char *str);
int					ft_error(char *str);
int					invalid_args(int argc, char **argv);
t_data				*init_data(int argc, char **argv);
void				*free_data(t_data *data);
t_data				*malloc_data(t_data *data);
t_fork				*init_forks(t_data *data);
void				*free_forks(t_fork *forks);
t_philo				*init_philos(t_data *data);
void				*free_philos(t_philo *philos);
t_fork				*mutex_forks(t_fork *forks, int n);
t_data				*mutex_data(t_data *data);
int					get_time(void);
int					m_sleep(t_philo *philo, int time);

#endif