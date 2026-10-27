/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 13:51:00 by adastugu          #+#    #+#             */
/*   Updated: 2026/02/23 15:35:37 by adastugu         ###   ########.fr       */
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

/// psleep() wakes up this many ms early; the main loop then polls the
/// remaining time precisely, so oversleeping can't make a philosopher late.
# define WAKE_MARGIN_MS 10

/// The simulation starts this many ms after the last thread is created.
/// It only has to cover main's start-flag loop (< 1 ms even for 2000
/// philosophers) plus one polling round, so it doesn't depend on the count.
# define START_MARGIN_MS 2

/// Size of each of the two log buffers, and the longest line we can append.
# define LOG_SIZE 1048576
# define LOG_LINE_MAX 64

typedef struct s_philo	t_philo;
typedef struct s_sim	t_sim;

typedef struct s_parse
{
	int					arg_count;
	char				**arg;
}						t_parse;

/// @brief Data shared by every thread.
/// The settings are written once before the threads start, then only read.
/// stop_lock guards the global `stop` (read by the monitors and main thread).
/// done_lock guards every philosopher's `eaten` and `done`.
/// print_lock guards the log buffer: it is only held to copy a line in,
/// never during write(), so a slow terminal can't stall a philosopher.
typedef struct s_sim
{
	int					nbof_philos;
	long				t2die;
	long				t2eat;
	long				t2sleep;
	int					musteat;
	long				start_time;

	int					stop;
	pthread_mutex_t		stop_lock;
	pthread_mutex_t		done_lock;
	pthread_mutex_t		print_lock;
	pthread_mutex_t		*forks;

	char				*log;
	char				*log_out;
	int					log_len;
	pthread_t			printer;

	t_philo				*philo;
	pthread_t			*philothread;
	pthread_t			monitor[2];
}						t_sim;

/// @brief Per-philosopher data.
/// `state` and `last_action` are only touched by the philosopher's own thread.
/// A philosopher holds both of its forks exactly while state == EATING.
/// philo_lock guards `last_meal`, `stop` and `started`, and is only ever taken
/// by this philosopher and main/the monitor. `stop` and `started` are private
/// copies of global events, so philosophers never wait on a global lock.
typedef struct s_philo
{
	int					id;
	int					state;
	long				last_action;

	long				last_meal;
	int					eaten;
	int					done;

	int					stop;
	int					started;
	pthread_mutex_t		philo_lock;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	t_sim				*sim;
}						t_philo;

// parse / args
int						parse(t_sim *sim, t_parse *parsing);
int						pre_parse(t_parse *parsing, int ac, char **av);
int						check_arg_count(t_parse *parsing);
void					freeparse(t_parse *parsing);
long					start_delay(int id, int nbof_philos, long t2eat);

// utils
size_t					ft_strlen(char *str);
int						nb_len(long nb);
int						ft_atoi(const char *str);
char					**ft_split(char const *s, char c);
char					*ft_strjoinall(char **av, char *res);
int						print_error(char *msg);
long					get_time_ms(void);
void					print_status(t_philo *p, char *msg);
int						psleep(long time_in_ms, t_philo *p);
int						wait_start(t_philo *p);

// routine
int						start_simulation(t_sim *sim);

// forks
void					lock_forks(t_philo *philo);
void					unlock_forks(t_philo *philo);

// ini
int						ini_sim(t_sim *sim);

// log
void					log_line(t_sim *sim, long time, int id, char *msg);
void					wait_log_space(t_sim *sim);
void					*printer(void *arg);
int						put_nbr(char *dst, long n);

// monitor
void					*death(void *arg);
void					*gluttony(void *arg);
void					wait_sim_stop(t_sim *sim);

// checks
int						check_single(t_philo *p);
int						check_stop(t_sim *sim);
int						check_done(t_philo *p);
void					set_last_meal(t_philo *p);
int						philo_stopped(t_philo *p);

// free
void					freeall(t_sim *sim);
void					destroy_mutexes(t_sim *sim);
void					stop_and_join(t_sim *sim, int philos, int monitors);
void					stop_all(t_sim *sim);

#endif