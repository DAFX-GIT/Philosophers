/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 17:45:04 by adastugu          #+#    #+#             */
/*   Updated: 2026/01/12 17:46:00 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lock_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
		philo->rfk = 1;
		pthread_mutex_lock(philo->left_fork);
		philo->lfk = 1;
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
		philo->lfk = 1;
		pthread_mutex_lock(philo->right_fork);
		philo->rfk = 1;
	}
}

void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	philo->rfk = 0;
	philo->lfk = 0;
}

void	unlock_frk_leftover(t_philo *p)
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
