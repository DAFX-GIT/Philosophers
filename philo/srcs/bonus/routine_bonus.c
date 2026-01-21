/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 10:56:03 by adastugu          #+#    #+#             */
/*   Updated: 2026/01/21 14:29:55 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	to_eat(t_process *p)
{
	if (p->state == THINKING)
	{
		lock_forks(p->sim, p);
		pthread_mutex_lock(&p->last_meal_lock);
		p->last_meal = get_time_ms();
		pthread_mutex_unlock(&p->last_meal_lock);
		print_status(p, "is eating");
		p->eaten++;
		p->state = EATING;
	}
}

int	to_sleep_and_think(t_process *p)
{
	if (p->state == EATING && get_time_ms() - p->last_meal >= p->sim->t2eat)
	{
		unlock_forks(p->sim, p);
		p->state = SLEEPING;
		p->last_action = get_time_ms();
		print_status(p, "is sleeping");
		check_done(p);
	}
	if (p->state == SLEEPING && get_time_ms()
		- p->last_action >= p->sim->t2sleep)
	{
		p->state = THINKING;
		print_status(p, "is thinking");
	}
	return (0);
}

void	stagger(t_process *p)
{
	if (p->sim->nbof_philos % 2 != 0)
	{
		if (p->philo_id == 0)
			;
		else if (p->philo_id == 1)
			psleep(p->sim->t2eat * 1.5);
		else if (p->philo_id == 2)
			psleep(p->sim->t2eat / 2);
		else
		{
			if (p->philo_id % 2 != 0)
				psleep(p->sim->t2eat * 2);
			else
				psleep(p->sim->t2eat);
		}
	}
	else
	{
		if (p->philo_id % 2 != 0)
			psleep(p->sim->t2eat);
	}
}

void	life(t_process *p)
{
	print_status(p, "is thinking");
	p->last_meal = get_time_ms();
	if (pthread_create(&p->death_monitor, NULL, &death, p))
	{
		p->sim->crash = 1;
		sem_post(p->sim->stop_sim);
		exit(0);
	}
	if (check_single(p))
		exit(0);
	stagger(p);
	while (1)
	{
		to_eat(p);
		to_sleep_and_think(p);
		usleep(500);
	}
	exit(0);
}

void	born2philo(t_sim *sim)
{
	int	id;

	sim->i = 0;
	sim->start_time = get_time_ms();
	while (sim->i < sim->nbof_philos)
	{
		id = fork();
		if (id < 0)
			handle_crash(sim, sim->i);
		if (id == 0)
			life(&sim->process[sim->i]);
		else
			sim->process[sim->i].pid = id;
		sim->i++;
	}
	if (pthread_create(&sim->glutony_monitor, NULL, &glutony, sim))
		handle_crash(sim, sim->nbof_philos);
	sem_wait(sim->stop_sim);
	sim->stop = 1;
	kill_process(sim, sim->nbof_philos);
	ending(sim, sim->nbof_philos);
}
