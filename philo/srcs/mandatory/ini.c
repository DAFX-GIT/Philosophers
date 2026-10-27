/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ini.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 11:53:38 by adastugu          #+#    #+#             */
/*   Updated: 2026/02/20 15:56:02 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ini_philo(t_sim *sim, int id)
{
	t_philo	*philo;

	philo = &sim->philo[id];
	philo->id = id;
	philo->state = THINKING;
	philo->eaten = 0;
	philo->done = 0;
	philo->stop = 0;
	philo->started = 0;
	philo->right_fork = &sim->forks[id];
	philo->left_fork = &sim->forks[(id + 1) % sim->nbof_philos];
	philo->sim = sim;
}

int	ini_sim(t_sim *sim)
{
	int	i;

	sim->stop = 0;
	sim->forks = malloc(sizeof(pthread_mutex_t) * sim->nbof_philos);
	sim->philo = malloc(sizeof(t_philo) * sim->nbof_philos);
	sim->philothread = malloc(sizeof(pthread_t) * sim->nbof_philos);
	sim->log = malloc(LOG_SIZE);
	sim->log_out = malloc(LOG_SIZE);
	if (!sim->forks || !sim->philo || !sim->philothread
		|| !sim->log || !sim->log_out)
		return (freeall(sim), print_error("Memory error\n"));
	if (pthread_mutex_init(&sim->stop_lock, NULL)
		|| pthread_mutex_init(&sim->print_lock, NULL)
		|| pthread_mutex_init(&sim->done_lock, NULL))
		return (freeall(sim), print_error("Mutex error\n"));
	i = 0;
	while (i < sim->nbof_philos)
	{
		if (pthread_mutex_init(&sim->forks[i], NULL)
			|| pthread_mutex_init(&sim->philo[i].meal_lock, NULL))
			return (freeall(sim), print_error("Mutex error\n"));
		ini_philo(sim, i);
		i++;
	}
	return (0);
}
