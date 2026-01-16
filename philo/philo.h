/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 13:51:00 by adastugu          #+#    #+#             */
/*   Updated: 2026/01/16 22:11:55 by adastugu         ###   ########.fr       */
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

typedef struct s_philo	t_philo;
typedef struct s_sim	t_sim;

typedef struct s_parse
{
	int					arg_count;
	char				**arg;
}						t_parse;

/// @brief this is shared data.
/// Writing here in a thread need a mutex to avoid race condition.
///(only read is ok tho i think)
typedef struct s_sim
{
	int					i;
	int					nbof_philos;
	int					philos_done;

	long				start_time;

	long				t2die;
	long				t2eat;
	long				t2sleep;
	int					musteat;
	t_philo				*philo;

	int					stop;
	pthread_mutex_t		stop_lock;
	pthread_mutex_t		print_lock;
	pthread_mutex_t		*forks;
	pthread_t			*philothread;
	pthread_t			monitor[2];
}						t_sim;

/// @brief this is data for each philosophers.
typedef struct s_philo
{
	int					id;
	int					state;

	int					done;

	long				last_meal;
	long				last_action;

	int					eaten;

	int					lfk;
	int					rfk;

	long				start_time;

	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	t_sim				*sim;
}						t_philo;

/* /// @brief this is shit that I use but im trying to remove to clean up code
typedef struct s_philo
{
	int					nbof_philos;
	int					i;
	long				t2die;
	long				t2eat;
	long				t2sleep;
	int					musteat;
	t_state				*pstate;
	pthread_mutex_t		*forks;
	t_sim				*sim;
}					t_philo; */

// parse
int						parse(t_sim *sim, t_parse *parsing);
int						nb_len(long nb);

// utils
size_t					ft_strlen(char *str);
int						nb_len(long nb);
long					get_time_ms(void);
void					print_status(t_philo *p, char *msg);
int						psleep(long time_in_ms, t_philo *p);
char					**ft_split(char const *s, char c);
char					*ft_strjoinall(char **av, char *res);

// routine
int						born2philo_ma(t_sim *sim);

// forks
void					lock_forks(t_philo *philo);
void					unlock_forks(t_philo *philo);
void					unlock_frk_leftover(t_philo *p);

// ini
void					ini_state(t_sim *sim, t_philo *philo,
							pthread_mutex_t *forks);
void					ini_sim(t_sim *sim);

// monitor
void					*death(void *arg);
void					*glutony(void *arg);
void					wait_sim_stop(t_sim *sim);

// checks
int						check_single(t_philo *p);
int						check_stop(t_philo *p);
void					check_done(t_philo *p);

// free
void					freeall(t_sim *sim);
void					freeparse(t_parse *parsing);

#endif