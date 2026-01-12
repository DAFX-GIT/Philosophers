/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 17:42:57 by adastugu          #+#    #+#             */
/*   Updated: 2026/01/12 17:47:46 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_single(t_philo *p)
{
	if (p->sim->nbof_philos == 1)
	{
		print_status(p, "has taken a fork");
		psleep(p->sim->t2die, p);
		return (1);
	}
	return (0);
}

int	check_stop(t_philo *p)
{
	pthread_mutex_lock(&p->sim->stop_lock);
	if (p->sim->stop)
	{
		pthread_mutex_unlock(&p->sim->stop_lock);
		return (1);
	}
	pthread_mutex_unlock(&p->sim->stop_lock);
	return (0);
}

void	check_done(t_philo *p)
{
	if (!p->done && p->sim->musteat > 0 && p->eaten >= p->sim->musteat)
		p->done = 1;
}
