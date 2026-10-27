/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 16:12:59 by adastugu          #+#    #+#             */
/*   Updated: 2026/01/26 18:17:51 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	close_sem(sem_t *sem)
{
	if (sem && sem != SEM_FAILED)
		sem_close(sem);
}

/// @brief Kills and reaps the first `philos` children. If the gluttony
/// monitor was started, wakes it wherever it is blocked and joins it:
/// philos_done in case nobody finished eating, print_lock in case a dead
/// philosopher kept it. It then sees `stop` and returns without printing.
void	end_simulation(t_sim *sim, int philos, int has_gluttony)
{
	int	i;

	sim->stop = 1;
	i = 0;
	while (i < philos)
		kill(sim->process[i++].pid, SIGKILL);
	i = 0;
	while (i < philos)
		waitpid(sim->process[i++].pid, NULL, 0);
	if (!has_gluttony)
		return ;
	i = 0;
	while (i++ < sim->nbof_philos)
		sem_post(sim->philos_done);
	sem_post(sim->print_lock);
	pthread_join(sim->gluttony_monitor, NULL);
}

void	freeall_exit(t_sim *sim, int status)
{
	int	i;

	i = 0;
	while (sim->process && i < sim->nbof_philos)
		close_sem(sim->process[i++].last_meal_lock);
	close_sem(sim->forks_pool);
	close_sem(sim->take_forks);
	close_sem(sim->print_lock);
	close_sem(sim->stop_sim);
	close_sem(sim->philos_done);
	unlink_sems();
	free(sim->process);
	free(sim);
	exit(status);
}
