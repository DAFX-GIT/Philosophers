/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 16:12:59 by adastugu          #+#    #+#             */
/*   Updated: 2026/01/14 17:06:51 by adastugu         ###   ########.fr       */
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

void	freeall(t_sim *sim, t_parse *parsing)
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
	freeparse(parsing);
}

void	ending(t_sim *sim)
{
	sim->i = 0;
	while (sim->i < sim->nbof_philos)
	{
		waitpid(-1, NULL, 0);
		pthread_mutex_destroy(&sim->process[sim->i].last_meal_lock);
		sim->i++;
	}
	pthread_cancel(sim->glutony_monitor);
	pthread_join(sim->glutony_monitor, NULL);
	sem_destroy(sim->forks_pool);
	sem_destroy(sim->print_lock);
	sem_destroy(sim->stop_sim);
	sem_destroy(sim->philos_done);
}
