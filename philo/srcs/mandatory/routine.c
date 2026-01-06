/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 18:02:48 by adastugu          #+#    #+#             */
/*   Updated: 2026/01/06 17:05:16 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ini_state(t_state *pstate, int i, t_philo *philo,
		pthread_mutex_t *forks)
{
	pstate->id = i;
	pstate->tl2live = philo->t2die;
	pstate->tl2eat = 0;
	pstate->tl2sleep = 0;
	pstate->lstuptim = get_time_ms();
	pstate->right_fork = &forks[i];
	pstate->left_fork = &forks[(i + 1) % philo->nbof_philos];
	pstate->is_eating = 0;
	pstate->is_sleeping = 0;
	pstate->elasp_time = 0;
	printf("Philosopher nb:%d is born\n", pstate->id);
}

void	update_time(t_state *pstate)
{
	long	now;

	now = get_time_ms();
	pstate->elasp_time = now - pstate->lstuptim;
	pstate->lstuptim = now;
	sub_clamped(&pstate->tl2live, pstate->elasp_time);
	sub_clamped(&pstate->tl2eat, pstate->elasp_time);
	sub_clamped(&pstate->tl2sleep, pstate->elasp_time);
}

void	lock_forks(t_state *pstate)
{
	if (pstate->id % 2 == 0)
	{
		pthread_mutex_lock(pstate->right_fork);
		printf("Philosopher nb:%d has taken his right fork\n", pstate->id);
		pthread_mutex_lock(pstate->left_fork);
		printf("Philosopher nb:%d has taken his left fork\n", pstate->id);
	}
	else
	{
		pthread_mutex_lock(pstate->left_fork);
		printf("Philosopher nb:%d has taken his left fork\n", pstate->id);
		pthread_mutex_lock(pstate->right_fork);
		printf("Philosopher nb:%d has taken his right fork\n", pstate->id);
	}
}
void unlock_forks(t_state *pstate)
{
	pthread_mutex_unlock(pstate->right_fork);
	pthread_mutex_unlock(pstate->left_fork);
}
void	*life(void *arg)
{
    t_state *pstate;
    pstate = (t_state *)arg;
	while (pstate->tl2live > 0)
	{
		update_time(pstate);
		if (pstate->is_eating == 0 && pstate->is_sleeping == 0)
		{
			lock_forks(pstate);
			pstate->is_eating = 1;
			pstate->tl2eat = pstate->t2eat;
			printf("Philosopher nb:%d has started eating\n", pstate->id);
		}
		if (pstate->is_eating == 1 && pstate->tl2eat == 0)
		{
			unlock_forks(pstate);
			pstate->is_eating = 0;
			pstate->is_sleeping = 1;
			pstate->tl2sleep = pstate->t2sleep;
			pstate->tl2live = pstate->t2die;
			printf("Philosopher nb:%d has finished eating and started sleeping\n", pstate->id);
		}
		if (pstate->is_sleeping == 1 && pstate->tl2sleep == 0)
		{
			pstate->is_sleeping = 0;
			printf("Philosopher nb:%d has finished sleeping\n", pstate->id);
		}
		usleep(1000);
	}
	printf("Philosopher nb:%d died\n", pstate->id);
	return (NULL);
}

void	born2philo(t_philo *philo)
{
	int				i;
	pthread_t		philothread[philo->nbof_philos];
	t_state			*pstate;
	pthread_mutex_t	*forks;

	i = 0;
	forks = malloc(sizeof(pthread_mutex_t) * philo->nbof_philos);
	pstate = malloc(sizeof(t_state) * philo->nbof_philos);
	while (i < philo->nbof_philos)
	{
		ini_state(&pstate[i], i, philo, forks);
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	i = 0;
	while (i < philo->nbof_philos)
	{
		pthread_create(&philothread[i], NULL, &life, &pstate[i]);
		i++;
	}
	usleep (8000000);
	i = 0;
	while (i < philo->nbof_philos)
	{
		pthread_join(philothread[i], NULL);
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}

// create thread
// monitor
// prio on who die first

/*
half can eat at the same time
fork have a mutex ?

*/