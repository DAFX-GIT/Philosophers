/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 12:11:39 by adastugu          #+#    #+#             */
/*   Updated: 2026/01/13 16:52:25 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/// @brief Forks are a pool (a counting semaphore), not individual objects.
/// take_forks makes "grab two forks" one step: without it, every
/// philosopher could hold one fork and wait forever for a second one.
/// With a single philosopher, the second sem_wait never returns, which is
/// exactly what should happen: they hold one fork and starve.
void	lock_forks(t_process *p)
{
	sem_wait(p->sim->take_forks);
	sem_wait(p->sim->forks_pool);
	print_status(p, "has taken a fork");
	sem_wait(p->sim->forks_pool);
	print_status(p, "has taken a fork");
	sem_post(p->sim->take_forks);
}

void	unlock_forks(t_process *p)
{
	sem_post(p->sim->forks_pool);
	sem_post(p->sim->forks_pool);
}
