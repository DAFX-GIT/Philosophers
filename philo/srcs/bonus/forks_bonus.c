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

void	lock_forks(t_sim *sim, t_process *p)
{
	sem_wait(sim->forks_pool);
	print_status(p, "has taken a fork");
	p->forks++;
	sem_wait(sim->forks_pool);
	print_status(p, "has taken a fork");
	p->forks++;
}

void	unlock_forks(t_sim *sim, t_process *p)
{
	sem_post(sim->forks_pool);
	sem_post(sim->forks_pool);
	p->forks--;
	p->forks--;
}
