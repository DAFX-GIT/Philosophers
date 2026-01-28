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

typedef struct s_process
{
	int						i;
	int						philo_id;
	int						pid;
	int						state;
	int						done;

	char					*var;
	sem_t					*last_meal_lock;
	long					last_meal;

	long					last_action;

	int						eaten;

	int						forks;

	long					start_time;
	pthread_t				death_monitor;
	int						sim_stop;

	t_sim					*sim;
}							t_process;

/// @brief this is shared data.
/// Writing here in a thread need a mutex to avoid race condition.
///(only read is ok tho i think)
typedef struct s_sim
{
	int						i;
	int						nbof_philos;

	long					start_time;

	long					t2die;
	long					t2eat;
	long					t2sleep;
	int						musteat;
	t_process				*process;

	int						stop;
	int						crash;

	sem_t					*philos_done;
	sem_t					*stop_sim;
	sem_t					*forks_pool;
	sem_t					*print_lock;

	pthread_t				glutony_monitor;

}							t_sim;

void						born2philo(t_sim *sim);
void						kill_process(t_sim *sim, int to_kill);

// monitor
void						*death(void *arg);
void						*glutony(void *arg);
void						print_status(t_process *p, char *msg);

// utils
int							psleep(long time_in_ms);
long						get_time_ms(void);
void						kill_process(t_sim *sim, int to_kill);

// checks
void						check_done(t_process *p);
int							check_single(t_process *p);

// forks
void						unlock_forks(t_sim *sim, t_process *p);
void						lock_forks(t_sim *sim, t_process *p);

// parse
int							parse(t_sim *sim, t_parse *parsing);

// ini
void						ini_sim(t_sim *sim);

// free
// void						freeall(t_sim *sim);
void						freeall_exit(t_sim *sim, int err);
void						freeparse(t_parse *parsing);
void						ending(t_sim *sim, int to_end);
void						handle_crash(t_sim *sim, int to_kill);

// minilft
char						*ft_strjoinall(char **av, char *res);
size_t						ft_strlen(char *str);
int							nb_len(long nb);
char						**ft_split(char const *s, char c);
char						*ft_itoa(int n);
int							ft_atoi(const char *str);

#endif