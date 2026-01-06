/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 13:51:00 by adastugu          #+#    #+#             */
/*   Updated: 2026/01/06 16:04:11 by adastugu         ###   ########.fr       */
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

typedef struct s_state
{
	int				id;
	long			tl2live;
	long			tl2eat;
	long			tl2sleep;
	int				eaten;
	long			lstuptim;
	long			elasp_time;
	struct timeval	tv;
	struct timezone	tz;
	long			t2die;
	long			t2eat;
	long			t2sleep;
	int				musteat;
	int				is_sleeping;
	int				is_eating;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}					t_state;

typedef struct s_philo
{
	int				nbof_philos;
	long			t2die;
	long			t2eat;
	long			t2sleep;
	int				musteat;
	struct timeval	tv;
	struct timezone	tz;
}					t_philo;

void				parse(t_philo *philo, int ac, char **av);

size_t				ft_strlen(char *str);
int					nb_len(long nb);
long				get_time_ms(void);
void			sub_clamped(long *value, long delta);

void				born2philo(t_philo *philo);

#endif