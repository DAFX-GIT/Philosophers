/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 18:02:48 by adastugu          #+#    #+#             */
/*   Updated: 2026/01/21 14:28:06 by adastugu         ###   ########.fr       */
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
		pthread_mutex_lock(&p->sim->done_lock);
		p->eaten++;
		pthread_mutex_unlock(&p->sim->done_lock);
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

void	stagger(t_philo *p)
{
	if (p->sim->nbof_philos % 2 != 0)
	{
		if (p->id == 0)
			;
		else if (p->id == 1)
			psleep(p->sim->t2eat * 1.5, p);
		else if (p->id == 2)
			psleep(p->sim->t2eat / 2, p);
		else
		{
			if (p->id % 2 != 0)
				psleep(p->sim->t2eat * 2, p);
			else
				psleep(p->sim->t2eat, p);
		}
	}
	else
	{
		if (p->id % 2 != 0)
			psleep(p->sim->t2eat, p);
	}
}

void	*life(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	print_status(p, "is thinking");
	set_last_meal(p);
	if (check_single(p))
		return (NULL);
	stagger(p);
	while (1)
	{
		to_eat(p);
		if (check_stop(p->sim))
			break ;
		if (to_sleep_and_think(p))
			break ;
		usleep(500);
	}
	unlock_frk_leftover(p);
	return (NULL);
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
	return (0);
}
