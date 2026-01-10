/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 18:02:48 by adastugu          #+#    #+#             */
/*   Updated: 2026/01/10 18:29:37 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ini_state(t_state *pstate, t_sim *sim, t_philo *philo,
		pthread_mutex_t *forks)
{
	pstate->id = philo->i;
	pstate->done = 0;
	pstate->last_meal = get_time_ms(pstate);
	pstate->last_action = get_time_ms(pstate);
	pstate->rfk = 0;
	pstate->lfk = 0;
	pstate->right_fork = &forks[philo->i];
	pstate->left_fork = &forks[(philo->i + 1) % philo->nbof_philos];
	pstate->state = THINKING;
	pstate->t2die = philo->t2die;
	pstate->t2eat = philo->t2eat;
	pstate->t2sleep = philo->t2sleep;
	pstate->eaten = 0;
	pstate->musteat = philo->musteat;
	pthread_mutex_init(&pstate->state_lock, NULL);
	pstate->sim = sim;
	pstate->start_time = get_time_ms(pstate);
	printf("Philosopher nb:%d is born\n", pstate->id);
}

void	to_eat(t_state *p)
{
	if (p->state == THINKING)
	{
		lock_forks(p);
		p->last_meal = get_time_ms(p);
		p->state = EATING;
		p->last_action = get_time_ms(p);
		print_status(p, "is eating");
	}
}

void	to_sleep_and_think(t_state *p)
{
	if (p->state == EATING && get_time_ms(p) - p->last_action >= p->t2eat)
	{
		unlock_forks(p);
		p->state = SLEEPING;
		p->last_action = get_time_ms(p);
		p->eaten++;
		print_status(p, "is sleeping");
	}
	if (p->state == SLEEPING && get_time_ms(p) - p->last_action >= p->t2sleep)
	{
		p->state = THINKING;
		print_status(p, "is thinking");
	}
}

void	*life(void *arg)
{
	t_state	*p;

	p = (t_state *)arg;
	p->last_meal = get_time_ms(p);
	/* if (p->id % 2 == 1)
		usleep(2000); */
	while (1)
	{
		pthread_mutex_lock(&p->sim->stop_lock);
		if (p->sim->stop)
		{
			pthread_mutex_unlock(&p->sim->stop_lock);
			break ;
		}
		pthread_mutex_unlock(&p->sim->stop_lock);
		to_eat(p);
		if (p->musteat > 0 && p->eaten >= p->musteat && !p->done)
		{
			p->done = 1;
			pthread_mutex_lock(&p->sim->stop_lock);
			p->sim->philos_done++;
			if (p->sim->philos_done >= p->sim->nbof_philos)
			{
				p->sim->stop = 1;
				pthread_mutex_lock(&p->sim->print_lock);
				printf("%ld %s\n", get_time_ms(p),
					"All philosophers have eaten their fill");
				pthread_mutex_unlock(&p->sim->print_lock);
			}
			pthread_mutex_unlock(&p->sim->stop_lock);
		}
		to_sleep_and_think(p);
		usleep(100);
	}
	unlock_frk_leftover(p);
	return (NULL);
}

void	ini_sim(t_sim *sim, t_philo *philo)
{
	sim->stop = 0;
	sim->philos_done = 0;
	sim->nbof_philos = philo->nbof_philos;
	pthread_mutex_init(&sim->stop_lock, NULL);
	pthread_mutex_init(&sim->print_lock, NULL);
}

void	born2philo(t_philo *philo)
{
	pthread_t		philothread[philo->nbof_philos];
	t_state			*pstate;
	pthread_mutex_t	*forks;
	t_sim			*sim;

	philo->i = 0;
	forks = malloc(sizeof(pthread_mutex_t) * philo->nbof_philos);
	pstate = malloc(sizeof(t_state) * philo->nbof_philos);
	sim = malloc(sizeof(t_sim));
	ini_sim(sim, philo);
	while (philo->i < philo->nbof_philos)
	{
		pthread_mutex_init(&forks[philo->i], NULL);
		ini_state(&pstate[philo->i], sim, philo, forks);
		philo->i++;
	}
	philo->i = 0;
	while (philo->i < philo->nbof_philos)
	{
		pthread_create(&philothread[philo->i], NULL, &life, &pstate[philo->i]);
		philo->i++;
	}
	while (!sim->stop)
	{
		philo->i = 0;
		while (philo->i < philo->nbof_philos)
		{
			pthread_mutex_lock(&sim->stop_lock);
			if (get_time_ms(&pstate[philo->i])
				- pstate[philo->i].last_meal >= pstate[philo->i].t2die)
			{
				print_status(&pstate[philo->i], "has died");
				sim->stop = 1;
				pthread_mutex_unlock(&sim->stop_lock);
				break ;
			}
			pthread_mutex_unlock(&sim->stop_lock);
			philo->i++;
		}
		usleep(500);
	}
	// usleep(800000);
	philo->i = 0;
	while (philo->i < philo->nbof_philos)
	{
		pthread_join(philothread[philo->i], NULL);
		pthread_mutex_destroy(&forks[philo->i]);
		philo->i++;
	}
}

// monitor
// prio on who die first

// death annoncement 10ms before
