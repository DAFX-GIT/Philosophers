/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 13:51:00 by adastugu          #+#    #+#             */
/*   Updated: 2026/01/09 17:18:23 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define EATING 0
# define SLEEPING 1
# define THINKING 2

typedef struct s_sim
{
	int				stop;
	int				philos_done;
	int				nbof_philos;
	pthread_mutex_t	stop_lock;
	pthread_mutex_t	print_lock;
}					t_sim;

typedef struct s_state
{
	int				id;
	int				state;

	int			done;

	long			last_meal;
	long			last_action;

	long			t2die;
	long			t2eat;
	long			t2sleep;

	int				eaten;
	int				musteat;

	int				lfk;
	int				rfk;

	long			start_time;

	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	state_lock;
	t_sim			*sim;
}					t_state;

typedef struct s_philo
{
	int				nbof_philos;
	int				i;
	long			t2die;
	long			t2eat;
	long			t2sleep;
	int				musteat;
}					t_philo;

void				parse(t_philo *philo, int ac, char **av);

size_t				ft_strlen(char *str);
int					nb_len(long nb);
long				get_time_ms(t_state *p);
void				print_status(t_state *p, char *msg);

void				born2philo(t_philo *philo);

void				lock_forks(t_state *pstate);
void				unlock_forks(t_state *pstate);
void				unlock_frk_leftover(t_state *p);

#endif