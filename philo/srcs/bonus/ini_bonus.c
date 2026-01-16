/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ini_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 10:57:42 by adastugu          #+#    #+#             */
/*   Updated: 2026/01/16 13:42:37 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ini_process(t_sim *sim, t_process *p) //,forks ?)
{
	p->philo_id = sim->i;
	p->forks = 0;
	p->state = THINKING;
	p->eaten = 0;
	p->sim = sim;
	p->sim_stop = 0;
	p->done = 0;
	pthread_mutex_init(&p->last_meal_lock, NULL);
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
}
