/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ini_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 10:57:42 by adastugu          #+#    #+#             */
/*   Updated: 2026/01/26 18:09:31 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ini_process(t_sim *sim, t_process *p)
{
	p->philo_id = sim->i;
	p->forks = 0;
	p->state = THINKING;
	p->eaten = 0;
	p->sim = sim;
	p->sim_stop = 0;
	p->done = 0;
	p->var = ft_itoa(p->philo_id + 100);
	if (!p->var)
		freeall_exit(sim, 1);
	sem_unlink(p->var);
	p->last_meal_lock = sem_open(p->var, O_CREAT, 0644, 1);
	sem_unlink(p->var);
	free (p->var);
	if (p->last_meal_lock == SEM_FAILED)
		freeall_exit(sim, 1);
}

void	ini_sim(t_sim *sim)
{
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/stop");
	sem_unlink("/done");
	sim->forks_pool = sem_open("/forks", O_CREAT, 0644, sim->nbof_philos);
	sim->print_lock = sem_open("/print", O_CREAT, 0644, 1);
	sim->stop_sim = sem_open("/stop", O_CREAT, 0644, 0);
	sim->philos_done = sem_open("/done", O_CREAT, 0644, 0);
	if (sim->forks_pool == SEM_FAILED || sim->print_lock == SEM_FAILED
		|| sim->stop_sim == SEM_FAILED || sim->philos_done == SEM_FAILED)
		freeall_exit(sim, 1);
	sim->process = malloc(sizeof(t_process) * sim->nbof_philos);
	if (!sim->process)
		freeall_exit(sim, 1);
	sim->i = 0;
	while (sim->i < sim->nbof_philos)
	{
		ini_process(sim, &sim->process[sim->i]);
		sim->i++;
	}
	sim->i = 0;
	sim->crash = 0;
}
