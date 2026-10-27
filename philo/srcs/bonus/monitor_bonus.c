/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 15:07:19 by adastugu          #+#    #+#             */
/*   Updated: 2026/01/26 18:03:48 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/// @brief Runs as a second thread inside each philosopher process.
/// On death it prints, wakes the parent, and keeps print_lock forever so
/// no other philosopher can print after "died".
void	*death(void *arg)
{
	t_process	*p;
	int			starving;

	p = (t_process *)arg;
	while (1)
	{
		sem_wait(p->last_meal_lock);
		starving = get_time_ms() - p->last_meal >= p->sim->t2die;
		sem_post(p->last_meal_lock);
		if (starving)
		{
			sem_wait(p->sim->print_lock);
			printf("%ld %d died\n", get_time_ms() - p->sim->start_time,
				p->id + 1);
			sem_post(p->sim->stop_sim);
			exit(0);
		}
		usleep(1000);
	}
}

/// @brief Parent-side thread: waits until every philosopher has posted
/// philos_done, then ends the simulation. `stop` is only read after
/// print_lock is acquired, so if a philosopher died first (and kept the
/// lock), this thread only wakes up once the parent has set `stop`.
void	*gluttony(void *arg)
{
	t_sim	*sim;
	int		i;

	sim = (t_sim *)arg;
	i = 0;
	while (i++ < sim->nbof_philos)
		sem_wait(sim->philos_done);
	sem_wait(sim->print_lock);
	if (sim->stop)
		return (NULL);
	printf("%ld All philosophers have eaten their fill\n",
		get_time_ms() - sim->start_time);
	sem_post(sim->stop_sim);
	return (NULL);
}
