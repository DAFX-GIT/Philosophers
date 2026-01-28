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

void	freeparse(t_parse *parsing)
{
	int	i;

	i = 0;
	if (parsing->arg)
		while (parsing->arg[i])
			free(parsing->arg[i++]);
	if (parsing->arg)
		free(parsing->arg);
}

void	freeall_exit(t_sim *sim, int err)
{
	sem_close(sim->forks_pool);
	sem_close(sim->print_lock);
	sem_close(sim->stop_sim);
	sem_close(sim->philos_done);
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/stop");
	sem_unlink("/done");
	if (sim->process)
		free(sim->process);
	if (sim)
		free(sim);
	exit(err);
}

void	ending(t_sim *sim, int to_end)
{
	sim->i = 0;
	while (sim->i < to_end)
	{
		waitpid(-1, NULL, 0);
		sem_close(sim->process[sim->i].last_meal_lock);
		sim->i++;
	}
	pthread_join(sim->glutony_monitor, NULL);
	/* sem_close(sim->forks_pool);
	sem_close(sim->print_lock);
	sem_close(sim->stop_sim);
	sem_close(sim->philos_done); */
}

void	handle_crash(t_sim *sim, int to_kill)
{
	kill_process(sim, to_kill);
	ending(sim, to_kill);
	write(2, "Not enough memory to run.\n", 26);
	freeall_exit(sim, 2);
}
