/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 19:35:53 by adastugu          #+#    #+#             */
/*   Updated: 2026/01/26 17:56:30 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
# include <wait.h>

# define EATING 0
# define SLEEPING 1
# define THINKING 2

typedef struct s_sim		t_sim;
typedef struct s_process	t_process;

typedef struct s_parse
{
	int						arg_count;
	char					**arg;
}							t_parse;

/// @brief Per-philosopher data. Every philosopher is its own process with
/// its own copy of this struct, so nothing here is shared with the others.
/// last_meal_lock only protects last_meal between the philosopher's two
/// threads: the main loop and its death monitor.
typedef struct s_process
{
	int						id;
	pid_t					pid;
	int						state;
	long					last_action;
	long					last_meal;
	int						eaten;
	int						done;
	sem_t					*last_meal_lock;
	pthread_t				death_monitor;
	t_sim					*sim;
}							t_process;

/// @brief Settings are copied into every child at fork(); the named
/// semaphores are the only state actually shared between processes.
/// forks_pool:  one token per fork on the table.
/// take_forks:  only one philosopher picks up forks at a time (no deadlock).
/// print_lock:  keeps log lines whole; never released after the last line.
/// stop_sim:    posted once by whoever ends the simulation.
/// philos_done: posted once by each philosopher who ate musteat times.
/// stop:        parent-only flag, tells the glutony monitor to stand down.
typedef struct s_sim
{
	int						nbof_philos;
	long					t2die;
	long					t2eat;
	long					t2sleep;
	int						musteat;
	long					start_time;

	int						stop;
	sem_t					*forks_pool;
	sem_t					*take_forks;
	sem_t					*print_lock;
	sem_t					*stop_sim;
	sem_t					*philos_done;

	t_process				*process;
	pthread_t				glutony_monitor;
}							t_sim;

// parse / args
int							parse(t_sim *sim, t_parse *parsing);
int							pre_parse(t_parse *parsing, int ac, char **av);
int							check_arg_count(t_parse *parsing);
void						freeparse(t_parse *parsing);
long						start_delay(int id, int nbof_philos, long t2eat);

// minilft
char						*ft_strjoinall(char **av, char *res);
size_t						ft_strlen(char *str);
int							nb_len(long nb);
char						**ft_split(char const *s, char c);
char						*ft_itoa(int n);
int							ft_atoi(const char *str);
int							print_error(char *msg);

// ini
void						ini_sim(t_sim *sim);
void						unlink_sems(void);

// routine
void						start_simulation(t_sim *sim);

// forks
void						lock_forks(t_process *p);
void						unlock_forks(t_process *p);

// monitor
void						*death(void *arg);
void						*glutony(void *arg);

// checks
void						check_done(t_process *p);

// utils
long						get_time_ms(void);
void						psleep(long time_in_ms);
void						print_status(t_process *p, char *msg);

// free
void						end_simulation(t_sim *sim, int philos,
								int has_glutony);
void						freeall_exit(t_sim *sim, int status);

#endif