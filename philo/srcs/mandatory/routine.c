/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 18:02:48 by adastugu          #+#    #+#             */
/*   Updated: 2026/01/16 22:37:15 by adastugu         ###   ########.fr       */
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
int join(t_sim *sim, int to_join)
{
	sim->stop = 1;
	sim->i = 0;
	while (sim->i < to_join)
	{
		pthread_join((sim->philothread[sim->i]), NULL);
		pthread_mutex_destroy(&sim->forks[sim->i]);
		sim->i++;
	}
	pthread_join((sim->monitor[0]), NULL);
	if (sim->musteat)
		pthread_join((sim->monitor[1]), NULL);
	return 0;
}
int	born2philo_ma(t_sim *sim)
{
	sim->start_time = get_time_ms();
	while (sim->i < sim->nbof_philos)
	{
		sim->philo[sim->i].start_time = sim->start_time;
		sim->philo[sim->i].last_meal = sim->start_time;
		if (pthread_create(&sim->philothread[sim->i], NULL, &life,
			&sim->philo[sim->i]))
				return (1 + join(sim, sim->i));
		sim->i++;
	}
	if (pthread_create(&sim->monitor[0], NULL, &death, sim))
		return (1 + join(sim, sim->nbof_philos));
	if (sim->musteat)
		if (pthread_create(&sim->monitor[1], NULL, &glutony, sim))
			return (1 + join(sim, sim->nbof_philos));
	wait_sim_stop(sim);
	join(sim, sim->nbof_philos);
	return 0;
}
