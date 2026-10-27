/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 18:13:02 by adastugu          #+#    #+#             */
/*   Updated: 2026/01/21 14:26:27 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	freeall(t_sim *sim)
{
	if (!sim)
		return ;
	free(sim->forks);
	free(sim->philo);
	free(sim->philothread);
	free(sim->log);
	free(sim->log_out);
	free(sim);
}

void	destroy_mutexes(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->nbof_philos)
	{
		pthread_mutex_destroy(&sim->philo[i].philo_lock);
		pthread_mutex_destroy(&sim->forks[i++]);
	}
	pthread_mutex_destroy(&sim->stop_lock);
	pthread_mutex_destroy(&sim->done_lock);
	pthread_mutex_destroy(&sim->print_lock);
}

/// @brief Sets the stop flag, then joins the first `philos` philosopher
/// threads, the first `monitors` monitor threads and the printer. Only
/// threads that were actually created are joined, so it is safe to call
/// on a partial start (the printer is always created first).
void	stop_and_join(t_sim *sim, int philos, int monitors)
{
	int	i;

	pthread_mutex_lock(&sim->print_lock);
	stop_all(sim);
	pthread_mutex_unlock(&sim->print_lock);
	i = 0;
	while (i < philos)
		pthread_join(sim->philothread[i++], NULL);
	i = 0;
	while (i < monitors)
		pthread_join(sim->monitor[i++], NULL);
	pthread_join(sim->printer, NULL);
}

/// @brief Ends the simulation: sets the global flag, then every
/// philosopher's own copy. The caller must hold print_lock, so any
/// print_status() that runs afterwards is guaranteed to see stop == 1.
void	stop_all(t_sim *sim)
{
	int	i;

	pthread_mutex_lock(&sim->stop_lock);
	sim->stop = 1;
	pthread_mutex_unlock(&sim->stop_lock);
	i = 0;
	while (i < sim->nbof_philos)
	{
		pthread_mutex_lock(&sim->philo[i].philo_lock);
		sim->philo[i].stop = 1;
		pthread_mutex_unlock(&sim->philo[i].philo_lock);
		i++;
	}
}
