/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ini.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 11:53:38 by adastugu          #+#    #+#             */
/*   Updated: 2026/01/28 11:41:12 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ini_state(t_sim *sim, t_philo *philo, pthread_mutex_t *forks)
{
	philo->id = sim->i;
	philo->done = 0;
	philo->rfk = 0;
	philo->lfk = 0;
	philo->right_fork = &forks[sim->i];
	philo->left_fork = &forks[(sim->i + 1) % sim->nbof_philos];
	philo->state = THINKING;
	philo->eaten = 0;
	philo->sim = sim;
}

int	ini_sim(t_sim *sim)
{
	sim->stop = 0;
	sim->philos_done = 0;
	sim->forks = malloc(sizeof(pthread_mutex_t) * sim->nbof_philos);
	sim->philo = malloc(sizeof(t_philo) * sim->nbof_philos);
	sim->philothread = malloc(sizeof(pthread_t) * sim->nbof_philos);
	if (!sim->forks || !sim->philo || !sim->philothread)
		return (write(2, "Memory error\n", 13), freeall(sim), 1);
	if (pthread_mutex_init(&sim->stop_lock, NULL)
		|| pthread_mutex_init(&sim->print_lock, NULL)
		|| pthread_mutex_init(&sim->done_lock, NULL))
		return (write(2, "Memory error\n", 13), freeall(sim), 1);
	sim->i = 0;
	while (sim->i < sim->nbof_philos)
	{
		if (pthread_mutex_init(&sim->forks[sim->i], NULL));
			return (write(2, "Memory error\n", 13), freeall(sim), 1);
		ini_state(sim, &sim->philo[sim->i], sim->forks);
		sim->i++;
	}
	sim->i = 0;
	return (0);
}
