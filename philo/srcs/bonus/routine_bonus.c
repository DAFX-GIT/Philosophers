/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 10:56:03 by adastugu          #+#    #+#             */
/*   Updated: 2026/01/16 14:46:22 by adastugu         ###   ########.fr       */
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

void	life(t_process *p)
{
	p->last_meal = get_time_ms();
	pthread_create(&p->death_monitor, NULL, &death, p);
	if (check_single(p))
		return ;
	if (p->philo_id % 2 == 1)
		usleep(8000);
	while (1)
	{
		to_sleep_and_think(p);
		if (p->sim->nbof_philos % 2 != 0 && p->sim->t2eat * 2
			- p->sim->t2sleep > 0)
			psleep((p->sim->t2eat * 2 - p->sim->t2sleep) * 0.5);
		to_eat(p);
	}
}

void	kill_process(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->nbof_philos)
	{
		sem_post(sim->philos_done);
		usleep(8000);
		kill(sim->process[i].pid, SIGKILL);
		i++;
	}
}

void	born2philo(t_sim *sim)
{
	int	id;

	sim->i = 0;
	sim->start_time = get_time_ms();
	while (sim->i < sim->nbof_philos)
	{
		id = fork();
		if (id == 0)
		{
			life(&sim->process[sim->i]);
			exit(0);
		}
		else
			sim->process[sim->i].pid = id;
		sim->i++;
	}
	pthread_create(&sim->glutony_monitor, NULL, &glutony, sim);
	sem_wait(sim->stop_sim);
	sim->stop = 1;
	kill_process(sim);
	ending(sim);
}
