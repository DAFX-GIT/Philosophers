/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 16:33:01 by adastugu          #+#    #+#             */
/*   Updated: 2026/01/21 14:00:13 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (0);
	else
		return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	psleep(long time_in_ms, t_philo *p)
{
	long	start_time;

	start_time = get_time_ms();
	while ((get_time_ms() - start_time) < time_in_ms)
	{
		if (check_stop(p->sim))
			return (1);
		check_done(p);
		usleep(100);
	}
	return (0);
}

void	set_last_meal(t_philo *p)
{
	pthread_mutex_lock(&p->sim->stop_lock);
	p->last_meal = get_time_ms();
	pthread_mutex_unlock(&p->sim->stop_lock);
}
