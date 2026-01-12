/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 18:02:48 by adastugu          #+#    #+#             */
/*   Updated: 2026/01/12 18:01:19 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	to_eat(t_philo *p)
{
	if (p->state == THINKING)
	{
		lock_forks(p);
		pthread_mutex_lock(&p->sim->stop_lock);
		p->last_meal = get_time_ms();
		pthread_mutex_unlock(&p->sim->stop_lock);
		print_status(p, "has taken a fork");
		print_status(p, "is eating");
		p->eaten++;
		p->state = EATING;
	}
}

int	to_sleep_and_think(t_philo *p)
{
	if (p->state == EATING && get_time_ms() - p->last_meal >= p->sim->t2eat)
	{
		unlock_forks(p);
		p->state = SLEEPING;
		p->last_action = get_time_ms();
		print_status(p, "is sleeping");
		if (psleep(p->sim->t2sleep - 50, p))
			return (1);
	}
	if (p->state == SLEEPING && get_time_ms()
		- p->last_action >= p->sim->t2sleep)
	{
		p->state = THINKING;
		print_status(p, "is thinking");
	}
	return (0);
}

void	*life(void *arg)
{
	t_philo	*p;
	long	system_latency;

	p = (t_philo *)arg;
	p->last_meal = get_time_ms();
	if (check_single(p))
		return (NULL);
	if (p->id % 2 == 1)
		usleep(1000);
	while (1)
	{
		if (check_stop(p))
			break ;
		if (to_sleep_and_think(p))
			break ;
		if (p->sim->nbof_philos % 2 != 0)
		{
			system_latency = 1;
			psleep(p->sim->t2eat * 2 - p->sim->t2sleep + system_latency, p);
		}
		to_eat(p);
	}
	unlock_frk_leftover(p);
	return (NULL);
}

void	born2philo(t_sim *sim)
{
	sim->start_time = get_time_ms();
	while (sim->i < sim->nbof_philos)
	{
		sim->philo[sim->i].start_time = sim->start_time;
		sim->philo[sim->i].last_meal = sim->start_time;
		pthread_create(&sim->philothread[sim->i], NULL, &life,
			&sim->philo[sim->i]);
		sim->i++;
	}
	pthread_create(&sim->monitor[0], NULL, &death, sim);
	if (sim->musteat)
		pthread_create(&sim->monitor[1], NULL, &glutony, sim);
	wait_sim_stop(sim);
	sim->i = 0;
	while (sim->i < sim->nbof_philos)
	{
		pthread_join((sim->philothread[sim->i]), NULL);
		pthread_mutex_destroy(&sim->forks[sim->i]);
		sim->i++;
	}
	pthread_join((sim->monitor[0]), NULL);
	if (sim->musteat)
		pthread_join((sim->monitor[1]), NULL);
}
