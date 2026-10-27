/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 17:42:57 by adastugu          #+#    #+#             */
/*   Updated: 2026/01/19 16:46:06 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/// @brief With a single fork, the only philosopher can never eat:
/// take the fork, wait to die, and let the death monitor report it.
int	check_single(t_philo *p)
{
	if (p->sim->nbof_philos != 1)
		return (0);
	print_status(p, "has taken a fork");
	psleep(p->sim->t2die, p);
	return (1);
}

int	check_stop(t_sim *sim)
{
	int	stop;

	pthread_mutex_lock(&sim->stop_lock);
	stop = sim->stop;
	pthread_mutex_unlock(&sim->stop_lock);
	return (stop);
}

int	check_done(t_philo *p)
{
	int	done;

	pthread_mutex_lock(&p->sim->done_lock);
	if (!p->done && p->sim->musteat > 0 && p->eaten >= p->sim->musteat)
		p->done = 1;
	done = p->done;
	pthread_mutex_unlock(&p->sim->done_lock);
	return (done);
}

void	set_last_meal(t_philo *p)
{
	pthread_mutex_lock(&p->philo_lock);
	p->last_meal = get_time_ms();
	pthread_mutex_unlock(&p->philo_lock);
}

/// @brief The philosopher's own copy of the stop flag. Its lock is shared
/// with the monitor only, so 1000 threads polling it don't queue up.
int	philo_stopped(t_philo *p)
{
	int	stop;

	pthread_mutex_lock(&p->philo_lock);
	stop = p->stop;
	pthread_mutex_unlock(&p->philo_lock);
	return (stop);
}
