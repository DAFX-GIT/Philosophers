/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 17:45:04 by adastugu          #+#    #+#             */
/*   Updated: 2026/01/09 18:05:36 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lock_forks(t_state *pstate)
{
	if (pstate->id % 2 == 0)
	{
		pthread_mutex_lock(pstate->right_fork);
		print_status(pstate, "has taken a fork");
		pstate->rfk = 1;
		pthread_mutex_lock(pstate->left_fork);
		print_status(pstate, "has taken a fork");
		pstate->lfk = 1;
	}
	else
	{
		pthread_mutex_lock(pstate->left_fork);
		print_status(pstate, "has taken a fork");
		pstate->lfk = 1;
		pthread_mutex_lock(pstate->right_fork);
		print_status(pstate, "has taken a fork");
		pstate->rfk = 1;
	}
}

void	unlock_forks(t_state *pstate)
{
	pthread_mutex_unlock(pstate->right_fork);
	pstate->rfk = 0;
	pthread_mutex_unlock(pstate->left_fork);
	pstate->lfk = 0;
}

void	unlock_frk_leftover(t_state *p)
{
	if (p->rfk)
	{
		pthread_mutex_unlock(p->right_fork);
		p->rfk = 0;
	}
	if (p->lfk)
	{
		pthread_mutex_unlock(p->left_fork);
		p->lfk = 0;
	}
}