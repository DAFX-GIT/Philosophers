/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 10:56:03 by adastugu          #+#    #+#             */
/*   Updated: 2026/01/26 17:55:07 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	to_eat(t_process *p)
{
	if (p->state != THINKING)
		return ;
	lock_forks(p);
	sem_wait(p->last_meal_lock);
	p->last_meal = get_time_ms();
	sem_post(p->last_meal_lock);
	print_status(p, "is eating");
	p->eaten++;
	p->state = EATING;
}

/// @brief Moves EATING -> SLEEPING -> THINKING once enough time has passed.
/// Called on every loop tick, so each transition happens as soon as it's due.
static void	to_sleep_and_think(t_process *p)
{
	if (p->state == EATING && get_time_ms() - p->last_meal >= p->sim->t2eat)
	{
		unlock_forks(p);
		p->state = SLEEPING;
		p->last_action = get_time_ms();
		print_status(p, "is sleeping");
		check_done(p);
	}
	if (p->state == SLEEPING
		&& get_time_ms() - p->last_action >= p->sim->t2sleep)
	{
		p->state = THINKING;
		print_status(p, "is thinking");
	}
}

/// @brief Body of a philosopher process. Never returns: the parent kills
/// the process when the simulation ends.
static void	life(t_process *p)
{
	print_status(p, "is thinking");
	p->last_meal = get_time_ms();
	if (pthread_create(&p->death_monitor, NULL, &death, p))
	{
		print_error("Thread error\n");
		sem_post(p->sim->stop_sim);
		exit(1);
	}
	psleep(start_delay(p->id, p->sim->nbof_philos, p->sim->t2eat));
	while (1)
	{
		to_eat(p);
		to_sleep_and_think(p);
		usleep(500);
	}
}

/// @brief Forks one process per philosopher, starts the gluttony monitor,
/// then sleeps until someone posts stop_sim (a death, or everyone ate).
void	start_simulation(t_sim *sim)
{
	int	i;

	sim->start_time = get_time_ms();
	i = 0;
	while (i < sim->nbof_philos)
	{
		sim->process[i].pid = fork();
		if (sim->process[i].pid < 0)
		{
			end_simulation(sim, i, 0);
			freeall_exit(sim, print_error("Fork error\n"));
		}
		if (sim->process[i].pid == 0)
			life(&sim->process[i]);
		i++;
	}
	if (pthread_create(&sim->gluttony_monitor, NULL, &gluttony, sim))
	{
		end_simulation(sim, i, 0);
		freeall_exit(sim, print_error("Thread error\n"));
	}
	sem_wait(sim->stop_sim);
	end_simulation(sim, i, 1);
}
