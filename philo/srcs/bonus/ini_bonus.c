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

/// @brief Each philosopher gets a private semaphore for last_meal.
/// It has to be a named one (sem_init isn't in the allowed functions), so
/// it is unlinked right away: the fd stays valid and no name is left behind.
static int	ini_process(t_sim *sim, int id)
{
	t_process	*p;
	char		*name;

	p = &sim->process[id];
	p->id = id;
	p->state = THINKING;
	p->sim = sim;
	name = ft_itoa(id + 100);
	if (!name)
		return (1);
	sem_unlink(name);
	p->last_meal_lock = sem_open(name, O_CREAT, 0644, 1);
	sem_unlink(name);
	free(name);
	return (p->last_meal_lock == SEM_FAILED);
}

void	unlink_sems(void)
{
	sem_unlink("/forks");
	sem_unlink("/take");
	sem_unlink("/print");
	sem_unlink("/stop");
	sem_unlink("/done");
}

void	ini_sim(t_sim *sim)
{
	int	i;

	unlink_sems();
	sim->forks_pool = sem_open("/forks", O_CREAT, 0644, sim->nbof_philos);
	sim->take_forks = sem_open("/take", O_CREAT, 0644, 1);
	sim->print_lock = sem_open("/print", O_CREAT, 0644, 1);
	sim->stop_sim = sem_open("/stop", O_CREAT, 0644, 0);
	sim->philos_done = sem_open("/done", O_CREAT, 0644, 0);
	if (sim->forks_pool == SEM_FAILED || sim->take_forks == SEM_FAILED
		|| sim->print_lock == SEM_FAILED || sim->stop_sim == SEM_FAILED
		|| sim->philos_done == SEM_FAILED)
		freeall_exit(sim, print_error("Semaphore error\n"));
	sim->process = malloc(sizeof(t_process) * sim->nbof_philos);
	if (!sim->process)
		freeall_exit(sim, print_error("Memory error\n"));
	memset(sim->process, 0, sizeof(t_process) * sim->nbof_philos);
	i = 0;
	while (i < sim->nbof_philos)
		if (ini_process(sim, i++))
			freeall_exit(sim, print_error("Semaphore error\n"));
}
